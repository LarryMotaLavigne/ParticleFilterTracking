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

    //Initialisation de l'attribut nom de l'objet Video
    //QFileInfo contient les informations d'un fichier (nom, extension...)
    QFileInfo fileInfo(file);
    //on souhaite uniquement récupérer le nom de fichier sans extension
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
    cap_ >> frameMatrix_;
    cv::Mat matrix = frameMatrix_.clone();
    Frame fr = getCurrentFrame();

    // Objects display
    if (!fr.getObjectsList().isEmpty() && isObjectsDisplay())
    {
        fr.drawObjects(matrix);
    }
    // Particles display
    if (!fr.getParticlesList().isEmpty())
    {
        for (int i = 0; i < graphIdToDisplay_.size(); ++i) {
            fr.drawParticle(matrix,graphIdToDisplay_[i]);
        }
    }
    QPixmap pixmap = Tools::cvMatToQPixmap(matrix);
    return pixmap;
}


/**
 * Get the current image with the drawing
 * @brief Video::getNextImage
 * @return pixmap the QPixmap object
 */
QPixmap Video::getCurrentImage()
{
    cv::Mat matrix = frameMatrix_.clone();
    Frame fr = getCurrentFrame();
    // Objects display
    if (!fr.getObjectsList().isEmpty() && isObjectsDisplay())
    {
        Tools::debugMessage("VIDEO : Affichage des objets");
        fr.drawObjects(matrix);
    }
    // Particles display
    if (!fr.getParticlesList().isEmpty() && graphIdToDisplay_.size()!=0)
    {
        Tools::debugMessage("VIDEO : Affichage des graphes");
        for (int i = 0; i < graphIdToDisplay_.size(); ++i) {
            fr.drawParticle(matrix,graphIdToDisplay_[i]);
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
 * @brief Video::getIndex
 * @return currentFrameIndex_ the index of the current frame
 */
unsigned int Video::getFrameIndex()
{
    return currentFrameIndex_;
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

void Video::setObjectsDisplay(bool isDisplay)
{
    displayObjects_ = isDisplay;
}

void Video::setGraphDisplay(bool isDisplay, unsigned int graphId)
{
    if(isDisplay)
    {
        Tools::debugMessage("setGraphDisplay TRUE",graphId);
        graphIdToDisplay_.append(graphId);
    }
    else
    {
        Tools::debugMessage("setGraphDisplay FALSE",graphId);
        for (int i = 0; i < graphIdToDisplay_.size(); ++i)
        {
            if(graphIdToDisplay_[i] == graphId)
            {
                graphIdToDisplay_.removeAt(i);
            }
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


void Video::setFrame(unsigned int framePosition)
{
    currentFrameIndex_ = framePosition;
    cap_.set(CV_CAP_PROP_POS_FRAMES,framePosition);
}

