#include "model/video.h"

/**
 * Default Constructor
 * @brief Video::Video
 */
Video::Video()
{
    this->filename_ = "";
}

/**
 * Constructor
 * @brief Video::Video
 * @param file the video file
 */
Video::Video(QString file)
{
    //opening the Video file
    const char* filename = file.toStdString().c_str();
    cap_.open(filename);

    // VideoCapture opening checking
    if(!cap_.isOpened())
    {
        Tools::debugMessage("Impossible de charger la vidéo");
    }

    QFileInfo fileInfo(file);

    // Get the filename without the extension
    QString nameFileWithoutExt = fileInfo.baseName();
    this->filename_ = nameFileWithoutExt;
    this->displayObjects_ = false;
}

/**
 * Destructor
 * @brief Video::~Video
 */
Video::~Video()
{

}


/**********************************************************************/
/*                               GETTER                               */
/**********************************************************************/

/**
 * Get the video filename
 * @brief Video::getFileName
 * @return filename_ the filename
 */
QString Video::getFileName()
{
    return filename_;
}

bool Video::isObjectsDisplay()
{
    return displayObjects_;
}

/**
 * Get the frames list
 * @brief Video::getFramesList
 * @return framesList_ the frames list
 */
QList<Frame>& Video::getFramesList()
{
    return framesList_;
}

/**
 * Get the VideoCapture object from the Video
 * @brief Video::getVideoCapture
 * @return cap the VideoCapture object
 */
cv::VideoCapture Video::getVideoCapture()
{
    return cap_;
}

/**
 * Get the number of frames in the video
 * @brief Video::getFramesCount
 * @return result the number of frames
 */
unsigned int Video::getFramesCount()
{
    return (int) cap_.get(CV_CAP_PROP_FRAME_COUNT);
}

/**
 * Get the frame matrix without writing
 * @brief Video::getFrameMatrix
 * @return result the frame matrix
 */
cv::Mat Video::getFrameMatrix()
{
    return frameMatrix_;
}


/**
 * Get the next image with the drawing
 * @brief Video::getNextImage
 * @return pixmap the QPixmap object
 */
QPixmap Video::getNextImage()
{
    cap_ >> frameMatrix_; // Get the next image from the VideoCapture
    return getCurrentImage();
}


/**
 * Get the current image with the drawing
 * @brief Video::getCurrentImage
 * @return pixmap the QPixmap object
 */
QPixmap Video::getCurrentImage()
{
    Frame fr = getCurrentFrame();
    cv::Mat matrix = frameMatrix_.clone(); // Create a matrix to draw on it

    // Objects display
    if (!fr.getObjectsList().isEmpty() && isObjectsDisplay())
    {
        Tools::debugMessage("VIDEO : Objects Display");
        fr.drawObjects(matrix);
    }
    // Graphs display
    if (!fr.getParticlesList().isEmpty() && particleIdSelected_.size()!=0)
    {
        Tools::debugMessage("VIDEO : Graphs Display");
        setParticleWeightSelected();
        for (int i = 0; i < particleIdSelected_.size(); ++i) {
            fr.drawParticle(matrix,positionSelected_[i],particleIdSelected_[i],particleWeightSelected_);
        }
    }
    QPixmap pixmap = Tools::cvMatToQPixmap(matrix);
    return pixmap;
}

/**
 * Get the current frame
 * @brief Video::getCurrentFrame
 * @return result the current frame
 */
Frame Video::getCurrentFrame()
{
    if (currentFrameIndex_ < framesList_.size())
    {
        return framesList_.at(currentFrameIndex_);
    }
    return NULL;

}

/**
 * Get the index of the current frame
 * @brief Video::getFrameIndex
 * @return currentFrameIndex_ the index of the current frame
 */
unsigned int Video::getFrameIndex()
{
    return currentFrameIndex_;
}

/**
 * Get the list of the graph id to display
 * @brief Video::getGraphIdToDisplay
 * @return currentFrameIndex_ the list of graph id to display
 */
QList<unsigned int> Video::getParticleIdSelected()
{
    return particleIdSelected_;
}

QList<unsigned int> Video::getPositionSelected()
{
    return positionSelected_;
}

/**********************************************************************/
/*                               SETTER                               */
/**********************************************************************/

/**
 * Set the index of the current frame
 * @brief Video::setIndex
 * @param index the new index
 */
void Video::setIndex(unsigned int frameIndex)
{
    currentFrameIndex_ = frameIndex;
}

/**
 * Set a boolean to trigger the object displaying
 * @brief Video::setObjectsDisplay
 * @param isDisplay a boolean to trigger the object displaying
 */
void Video::setObjectsDisplay(bool isDisplay)
{
    displayObjects_ = isDisplay;
}

/**
 * Append/remove to 2 lists (id and weight) of particles selected
 * @brief Video::setParticleDisplay
 * @param index the new index
 */
void Video::setParticleDisplay(bool isDisplay,unsigned int position, unsigned int particleId, double particleWeight)
{
    if(isDisplay)
    {
        Tools::debugMessage("setParticleDisplay TRUE");
        Tools::debugMessage("setParticleDisplay - POSITION", position);
        Tools::debugMessage("setParticleDisplay - ID",particleId);
        Tools::debugMessage("setParticleDisplay - WEIGHT",particleWeight);
        if(!particleIdSelected_.contains(particleId))
        {
            positionSelected_.append(position);
            particleIdSelected_.append(particleId);
            particleWeightSelected_.append(particleWeight);
        }
    }
    else
    {
        Tools::debugMessage("setParticleDisplay FALSE",particleId);
        for (int i = 0; i < particleIdSelected_.size(); ++i)
        {
            if(particleIdSelected_[i] == particleId)
            {
                positionSelected_.removeAt(i);
                particleIdSelected_.removeAt(i);
                particleWeightSelected_.removeAt(i);
            }
        }
    }
}


/**
 * Update the old list based on a new one
 * @brief Video::setParticleIdSelected
 * @param newParticleIdSelected the new list
 */
void Video::setParticleIdSelected(QList<unsigned int> newParticleIdSelected)
{
    particleIdSelected_.clear();
    particleIdSelected_ = newParticleIdSelected;
}


/**
 * Update the old list based on a new one
 * @brief Video::setParticleWeightSelected
 */
void Video::setParticleWeightSelected()
{
    particleWeightSelected_.clear();
    Frame fr = getCurrentFrame();
    for (int i = 0; i < fr.getParticlesList().size(); ++i) {
        if(particleIdSelected_.contains(fr.getParticlesList().at(i)->getParticleId()))
        {
            particleWeightSelected_.append(fr.getParticlesList().at(i)->getWeightParticle());
        }
    }
}


/**********************************************************************/
/*                           ADDING FUNCTION                          */
/**********************************************************************/

/**
 * Add a new frame to the frames list
 * @brief Video::addFrame
 * @param frame the new frame to add
 */
void Video::addFrame(Frame frame)
{
    framesList_.append(frame);
}


/**********************************************************************/
/*                              NAVIGATION                            */
/**********************************************************************/

/**
 * Increment the frame index to go to the next frame
 * @brief Video::next
 */
void Video::next()
{
    setFrame(currentFrameIndex_+1);
}

/**
 * Decrement the frame index to go to the previous frame
 * @brief Video::previous
 */
void Video::previous()
{
    setFrame(currentFrameIndex_-1);
}


/**
 * Set a specific frame based on the frame position
 * @brief Video::setFrame
 * @param framePosition the frame position
 */
void Video::setFrame(unsigned int framePosition)
{
    currentFrameIndex_ = framePosition;
    cap_.set(CV_CAP_PROP_POS_FRAMES,framePosition);
}

