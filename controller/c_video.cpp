#include "controller/c_video.h"

/**
 * Constructor
 * @brief C_Video::C_Video
 * @param parent the parent object
 */
C_Video::C_Video(QObject *parent) : QObject(parent)
{

}

/**
 * Destructor
 * @brief C_Video::~C_Video
 */
C_Video::~C_Video()
{

}

/**
 * Get the loaded video
 * @brief C_Video::getLoadedVideo
 * @return the loaded video
 */
Video* C_Video::getLoadedVideo()
{
    return this->loadedVideo;
}


/**********************************************************************/
/*                               TIMER                                */
/**********************************************************************/

/**
 * Start or stop the timer if the play button is trigger
 * @brief C_Video::startOrStopTimer
 */
void C_Video::startOrStopTimer()
{
    MainWindow *w = (MainWindow *)parent();

    // If the timer isn't active (The video isn't playing), we active it
    if(!w->tmrTimer->isActive())
    {
        w->tmrTimer->start();
        w->ui->playButton->setIcon(QIcon(":/logo/pause"));
        w->ui->playButton->setShortcut(Qt::Key_Space);
        // By default, we disable the previous and next button
        w->ui->previousButton->setEnabled(false);
        w->ui->nextButton->setEnabled(false);
        w->ui->boutonRevenirDebut->setEnabled(false);
        Tools::debugMessage("----- PLAY -----");
    }
    // If the timer is active (The video is playing), we disable it
    else
    {
        w->tmrTimer->stop();
        w->ui->playButton->setIcon(QIcon(":/logo/play"));
        w->ui->playButton->setShortcut(Qt::Key_Space);
        // By default, we enable the previous and next button
        w->ui->previousButton->setEnabled(true);
        w->ui->nextButton->setEnabled(true);
        w->ui->boutonRevenirDebut->setEnabled(true);
        Tools::debugMessage("----- PAUSE -----");
    }

}


/**********************************************************************/
/*                             OPEN/READ                              */
/**********************************************************************/

/**
 * Read the loaded video
 * @brief C_Video::readVideo
 */
void C_Video::readVideo()
{
    MainWindow *w = (MainWindow *)parent();

    // Next Image from the Loaded Video
    loadedVideo->next();
    QPixmap image = loadedVideo->getNextImage();
    Frame frame = loadedVideo->getCurrentFrame();

    // If the image isn't null, we display
    if(!image.isNull())
    {

        w->addParticles(frame);
        w->viewerUpdate(image);

        Tools::debugMessage("Frame Index", loadedVideo->getFrameIndex());

    }
    // Else, we stop the timer and go back to the first frame
    else
    {
        // Timer stop
        startOrStopTimer();
        // Reset
        loadedVideo->getVideoCapture().set(CV_CAP_PROP_POS_FRAMES,0);
        loadedVideo->setIndex(0);

        // Display the first image
        image = loadedVideo->getNextImage();
        frame = loadedVideo->getCurrentFrame();
        w->viewerUpdate(image);

        Tools::debugMessage("Frame Index", loadedVideo->getFrameIndex());

        // Disable the previous button
        w->ui->previousButton->setEnabled(false);
    }
}

/**
 * Open a video
 * @brief C_Video::openVideo
 * @return true if it succeeds, else false
 */
bool C_Video::openVideo()
{
    MainWindow *w = (MainWindow *)parent();


    Tools::debugMessage("###################");
    Tools::debugMessage("C_Video::openVideo : Start");

    // File location
    QString title = "Open a video";
    QString directory = "C://";

    QString fichier = QFileDialog::getOpenFileName(w, title, directory, tr("Videos (*.avi *.mov *.mpg *.mp4 *.asf)"));

    // Check the file importation
    if (fichier.isEmpty())
    {
        Tools::debugMessage("Video loading cancel");
        w->ui->statusBar->showMessage("Video loading Cancel",0);
        return false;
    }

    w->ui->statusBar->showMessage("Video Loading...",0);

    Tools::debugMessage("Filename", fichier);
    Tools::debugMessage("Video opening");

    // Video Object Creation
    Tools::debugMessage("Video Init BEGIN");
    loadedVideo = new Video(fichier);
    loadedVideo->setIndex(0);
    Tools::debugMessage("Video init END");

    // Frame count in the video
    unsigned int count = loadedVideo->getFramesCount();
    Tools::debugMessage("Number of frames", count);

    // Frame Object Creation
    Tools::debugMessage("Frame Init BEGIN");
    for (unsigned int i=0;i<count;i++)
    {
        Frame * myFrame = new Frame(i);
        loadedVideo->addFrame(*myFrame);
    }
    Tools::debugMessage("Frame Init END");


    // VideoCapture Parameter
    cv::VideoCapture cap = loadedVideo->getVideoCapture();

    // Timer initialization according the video frame rate
    w->tmrTimer->setInterval(1000/cap.get(CV_CAP_PROP_FPS));

    Tools::debugMessage("Interval Timer value", 1000/cap.get(CV_CAP_PROP_FPS));

    // First Image/Frame
    QPixmap image = loadedVideo->getNextImage();
    Frame fr = loadedVideo->getCurrentFrame();

    // Add Particles in the table
    w->addParticles(fr);

    Tools::debugMessage("Frame Index", loadedVideo->getFrameIndex());

    // Display the first image in the viewer
    w->ui->viewer->setGeometry(QRect(QPoint(500,500),QPoint(1200,1200)));
    w->viewerUpdate(image);

    //Enable buttons
    w->ui->nextButton->setEnabled(true);
    w->ui->playButton->setEnabled(true);
    w->ui->boutonRevenirDebut->setEnabled(true);

    // Enable action openAlgorithm
    w->ui->action_openAlgorithm->setEnabled(true);

    // define spinBox maximum value
    w->ui->spinBoxFrame->setMaximum((int)count);

    w->ui->statusBar->showMessage("Video loading Complete !",0);

    Tools::debugMessage("C_Video::openVideo : End");
    Tools::debugMessage("###################");


    return true;
}


/**********************************************************************/
/*                               FRAME                                */
/**********************************************************************/


/**
 * Go to the next frame
 * @brief C_Video::goToNextFrame
 */
void C_Video::goToNextFrame()
{
    MainWindow *w = (MainWindow *)parent();

    // Enable previous button in every case
    w->ui->previousButton->setEnabled(true);

    // Get the next frame from the loaded video
    loadedVideo->next();
    QPixmap image = loadedVideo->getNextImage();
    Frame fr = loadedVideo->getCurrentFrame();

    // Update the particles in the table
    w->addParticles(fr);
    w->selectParticles(getLoadedVideo());

    // Update the viewer
    w->viewerUpdate(image);

    Tools::debugMessage("Frame Index", loadedVideo->getFrameIndex());

    //If we are at the end of the list, we disable the next button
    if(loadedVideo->getFrameIndex()==loadedVideo->getFramesList().size()-1)
    {
        w->ui->nextButton->setEnabled(false);
    }

}

/**
 * Go to previous frame
 * @brief C_Video::goToPreviousFrame
 */
void C_Video::goToPreviousFrame()
{
    MainWindow *w = (MainWindow *)parent();

    // Enable next button in every case
    w->ui->nextButton->setEnabled(true);

    // Get the previous frame from the loaded video
    loadedVideo->previous();
    QPixmap image = loadedVideo->getNextImage();
    Frame fr = loadedVideo->getCurrentFrame();

    // Update the particles in the table
    w->addParticles(fr);
    w->selectParticles(loadedVideo);

    // Update the viewer
    w->viewerUpdate(image);

    Tools::debugMessage(" Frame Index", loadedVideo->getFrameIndex());

    //If we are at the begin of the list, we disable the previous button
    if(loadedVideo->getFrameIndex()==0)
    {
        w->ui->previousButton->setEnabled(false);
    }
}


void C_Video::goToSpecificFrame()
{
    /*
    MainWindow *w = (MainWindow *)parent();

    //on s'assure que le bouton Précédent soit activé dans tous les cas
    w->ui->previousButton->setEnabled(true);

    //on insère la frame suivante dans le Label de la fenêtre
    //videoChargee->next();
    videoChargee->setIndice(w->ui->spinBoxFrame->value());
    QPixmap image = videoChargee->getCurrentImage();
    Frame fr = videoChargee->getCurrentFrame();

    //ajout des particules dans le tableau
    w->addParticles(fr);

    w->setFrameIntoLabel(image);

    //indice courant de frame
    Tools::debugMessage("Indice courant de frame", videoChargee->getIndice());

    //on désactive le bouton Suivant si nous sommes à la fin de la liste
    if(videoChargee->getIndice()==videoChargee->getFrames().size()-1){
        w->ui->nextButton->setEnabled(false);
    }*/
}

/**
 * Go back to the first frame from the loaded video
 * @brief C_Video::returnToFirstFrame
 */
void C_Video::returnToFirstFrame()
{
    MainWindow *w = (MainWindow *)parent();

    // Video Capture object from the loaded video
    cv::VideoCapture cap = loadedVideo->getVideoCapture();

    // Reset the loaded video index and the VideoCapture index
    loadedVideo->setIndex(0);
    cap.set(CV_CAP_PROP_POS_FRAMES,0);

    // Get the next image from the capture (first frame)
    QPixmap image = loadedVideo->getNextImage();
    Frame frame = loadedVideo->getCurrentFrame();

    // Update the particle table
    w->addParticles(frame);

    // Update the viewer
    w->viewerUpdate(image);

    Tools::debugMessage("Frame Index", loadedVideo->getFrameIndex());

    //Disable previous button, Enable next and play button
    w->ui->previousButton->setEnabled(false);
    w->ui->nextButton->setEnabled(true);
    w->ui->playButton->setEnabled(true);

}

/**********************************************************************/
/*                              DISPLAY                               */
/**********************************************************************/

/**
 * Display the object on the current frame
 * @brief C_Video::displayObjects
 */
void C_Video::displayObjects(){
    // If the loaded video get the checkbox check
     if(getLoadedVideo()->isObjectsDisplay())
     {
        getLoadedVideo()->setObjectsDisplay(false);
        Tools::debugMessage("Box unchecked");
     }
     else
     {
        getLoadedVideo()->setObjectsDisplay(true);
        Tools::debugMessage("Box checked");
     }

     // We refresh the viewer
     MainWindow *w = (MainWindow *)parent();
     QPixmap pixmap = getLoadedVideo()->getCurrentImage();
     w->viewerUpdate(pixmap);
}


/**
 * Display the graphs on the current frame
 * @brief C_Video::displayGraphs
 */
void C_Video::displayGraphs(QTableWidgetItem* item)
{
    // If an item (a graph) is selected, we get the ID
    int rowValue = item->row();
    int particleId = item->tableWidget()->item(rowValue,ID_PARTICLE_TABLEVIEW)->text().toInt();
    double particleWeight = item->tableWidget()->item(rowValue,WEIGHT_PARTICLE_TABLEVIEW)->text().toDouble();
    if(item->isSelected())
    {
        if(getLoadedVideo()->getParticleIdSelected().size() < MAX_PARTICLE_DISPLAY)
        {
            // We add the id to the list
            getLoadedVideo()->setParticleDisplay(true, particleId, particleWeight);
        }
        else
        {
            // Deselect table widget item
            item->tableWidget()->selectRow(rowValue);
        }
    }
    else
    {
        // We remove the id to the list
        getLoadedVideo()->setParticleDisplay(false, particleId, particleWeight);
    }

    // We refresh the viewer
    MainWindow *w = (MainWindow *)parent();
    QPixmap pixmap = getLoadedVideo()->getCurrentImage();
    w->viewerUpdate(pixmap);
}

