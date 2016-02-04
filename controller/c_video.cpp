#include "controller/c_video.h"

/**
 * Le constructeur
 * @brief C_Video::C_Video
 * @param parent
 */
C_Video::C_Video(QObject *parent) : QObject(parent)
{

}

/**
 * Le destructeur
 * @brief C_Video::~C_Video
 */
C_Video::~C_Video()
{

}

/**
 * Retour à la première frame de la vidéo chargée au sein de la plateforme
 * @brief C_Video::returnToFirstFrame
 */
void C_Video::returnToFirstFrame()
{
    MainWindow *w = (MainWindow *)parent();

    //VideoCapture de l'objet Video
    cv::VideoCapture cap = loadedVideo->getVideoCapture();

    //on réinitialise l'indice de l'objet vidéo à 0, ainsi que celui de l'attribut VideoCapture
    loadedVideo->setIndex(0);
    cap.set(CV_CAP_PROP_POS_FRAMES,0);

    //on affiche la première image de la vidéo
    QPixmap image = loadedVideo->getCurrentImage();
    Frame frame = loadedVideo->getCurrentFrame();

    //ajout des particules dans la tableau
    w->addParticles(frame);

    w->viewerUpdate(image);

    //indice courant de frame
    Tools::debugMessage("Indice courant de frame", loadedVideo->getFrameIndex());

    //Bouton Précédent inactif, boutons Next et Lecture actifs
    w->ui->previousButton->setEnabled(false);
    w->ui->nextButton->setEnabled(true);
    w->ui->playButton->setEnabled(true);

}

/**
 * Démarrage ou arrêt du Timer suivant la lecture ou non de la vidéo
 * @brief C_Video::startOrStopTimer
 */
void C_Video::startOrStopTimer()
{
    MainWindow *w = (MainWindow *)parent();

    //si le timer n'est pas actif (ie. pas de lecture vidéo en cours), on l'active et la lecture de la vidéo se fait
    if(!w->tmrTimer->isActive())
    {
        w->tmrTimer->start();
        w->ui->playButton->setIcon(QIcon(":/logo/pause"));
        w->ui->playButton->setShortcut(Qt::Key_Space);
        //par défaut durant la lecture on désactive les boutons de visualisation frame par frame
        w->ui->previousButton->setEnabled(false);
        w->ui->nextButton->setEnabled(false);
        w->ui->boutonRevenirDebut->setEnabled(false);
        Tools::debugMessage("-----DEMARRAGE DE LA LECTURE-----");
        //si le timer est actif (ie. lecture vidéo en cours), on le désactive et la lecture de la vidéo s'arrête
    }
    else
    {
        w->tmrTimer->stop();
        w->ui->playButton->setIcon(QIcon(":/logo/play"));
        w->ui->playButton->setShortcut(Qt::Key_Space);
        //par défaut lorsqu'il n'y a pas lecture on active les boutons de visualisation frame par frame
        w->ui->previousButton->setEnabled(true);
        w->ui->nextButton->setEnabled(true);
        w->ui->boutonRevenirDebut->setEnabled(true);
        Tools::debugMessage("-----ARRET DE LA LECTURE-----");
    }

}

void C_Video::displayObjects(){
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

     MainWindow *w = (MainWindow *)parent();
     QPixmap pixmap = getLoadedVideo()->refreshCurrentImage();
     w->viewerUpdate(pixmap);
}


void C_Video::displayGraphs(QTableWidgetItem* item)
{
    int rowValue = item->row();
    int idGraph = item->tableWidget()->item(rowValue,0)->text().toInt();
    if(item->isSelected())
    {
        getLoadedVideo()->setGraphDisplay(true, idGraph);
    }
    else
    {
        getLoadedVideo()->setGraphDisplay(false, idGraph);
    }

    MainWindow *w = (MainWindow *)parent();
    QPixmap pixmap = getLoadedVideo()->refreshCurrentImage();
    w->viewerUpdate(pixmap);
}


/**
 * Lecture de la vidéo chargée au sein de la plateforme
 * @brief C_Video::readVideo
 */
void C_Video::readVideo()
{
    MainWindow *w = (MainWindow *)parent();

    //on récupère l'image courante
    loadedVideo->next();
    QPixmap image = loadedVideo->getCurrentImage();
    Frame frame = loadedVideo->getCurrentFrame();

    //si l'image courante est pas nulle, alors on l'affiche au sein du QLabel
    if(!image.isNull())
    {
        //ajout des particules dans la tableau
        w->addParticles(frame);
        w->viewerUpdate(image);

        //indice courant de frame
        Tools::debugMessage("Indice courant de frame", loadedVideo->getFrameIndex());

        //si l'image est nulle on arrête la lecture et on revient à la première frame de la vidéo
    }
    else
    {
        //arrêt du Timer
        startOrStopTimer();
        //remise à zéro de l'indice de VideoCapture ainsi que de l'objet Video
        loadedVideo->getVideoCapture().set(CV_CAP_PROP_POS_FRAMES,0);
        loadedVideo->setIndex(0);
        //on réaffiche par défaut la première frame de vidéo
        image = loadedVideo->getCurrentImage();
        frame = loadedVideo->getCurrentFrame();
        w->viewerUpdate(image);

        //indice courant de frame
        Tools::debugMessage("Indice courant de frame", loadedVideo->getFrameIndex());

        //le bouton Précédent est désactivé
        w->ui->previousButton->setEnabled(false);
    }
}

/**
 * Ouverture d'une vidéo sélectionnée au sein d'une arborescence de fichier
 * @brief C_Video::ouvrirVideo
 * @return true si réussite de l'ouverture de la vidéo, false sinon
 */
bool C_Video::openVideo()
{
    MainWindow *w = (MainWindow *)parent();

    Tools::debugMessage("Ouverture de la fenêtre d'importation de la vidéo");
    //récupération de l'emplacement du fichier à ouvrir
    QString title = "Open a video";
    QString directory = "C://";

    QString fichier = QFileDialog::getOpenFileName(w, title, directory, tr("Videos (*.avi *.mov *.mpg *.mp4 *.asf)"));

    //vérification de la bonne ouverture de fichier
    if (fichier.isEmpty())
    {
        Tools::debugMessage("Annulation de l'ouverture d'une vidéo");
        w->ui->statusBar->showMessage("Video loading Cancel",0);
        return false;
    }
    //on affiche un message dans la barre de statut
    w->ui->statusBar->showMessage("Chargement de la vidéo en cours...",0);

    Tools::debugMessage("Nom du fichier sélectionné", fichier);
    Tools::debugMessage("Ouverture de la vidéo");

    //CONSTRUCTION DE L'OBJET VIDEO
    Tools::debugMessage("Initialisation de l'objet Video");
    loadedVideo = new Video(fichier);
    loadedVideo->setIndex(0);
    Tools::debugMessage("Initialisation de l'objet Video terminée");

    //nombre de frames dans la vidéo sélectionnée
    unsigned int count = loadedVideo->getFramesCount();
    Tools::debugMessage("Nombre de frames", count);

    //CONSTRUCTION DES OBJETS FRAMES
    Tools::debugMessage("Initialisation des objets Frame");
    for (int i=0;i<count;i++)
    {
        Frame * maFrame = new Frame(i);
        loadedVideo->addFrame(*maFrame);
    }

    Tools::debugMessage("Initialisation des objets Frame terminée");

    //On travaille avec la VideoCapture de l'objet Video
    cv::VideoCapture cap = loadedVideo->getVideoCapture();

    //on initialise l'intervalle du Timer en fonction du Frame Rate de la vidéo sélectionnée
    w->tmrTimer->setInterval(1000/cap.get(CV_CAP_PROP_FPS));

    Tools::debugMessage("Valeur de l'intervalle de Timer", 1000/cap.get(CV_CAP_PROP_FPS));

    //récupération de la 1ère frame au format QPixmap
    QPixmap image = loadedVideo->getCurrentImage();
    Tools::debugMessage("getCurrentImage OK");
    Frame fr = loadedVideo->getCurrentFrame();
    Tools::debugMessage("getCurrentFrame OK");

    //ajout des particules dans la tableau
    w->addParticles(fr);

    //indice courant de frame
    Tools::debugMessage("Indice courant de frame", loadedVideo->getFrameIndex());

    //AFFICHAGE DE LA PREMIERE FRAME DE L'OBJET VIDEO DANS LA MAINWINDOW
    w->ui->viewer->setGeometry(QRect(QPoint(500,500),QPoint(1200,1200)));
    //on charge la première frame de la vidéo
    w->viewerUpdate(image);

    //on rend le bouton Frame suivante actif, ainsi que le bouton de lecture et le retour à la première frame
    w->ui->nextButton->setEnabled(true);
    w->ui->playButton->setEnabled(true);
    w->ui->boutonRevenirDebut->setEnabled(true);

    //on rend accessible la fonction d'import d'un algorithme
    w->ui->action_openAlgorithm->setEnabled(true);

    //on active la spinBox indiquant le numéro de frame courant
    //*
    //w->ui->spinBoxFrame->setEnabled(true);
    w->ui->spinBoxFrame->setMaximum((int)count);
    /* */

    //on affiche un message dans la barre de statut
    w->ui->statusBar->showMessage("Chargement de la vidéo terminé !",0);
    return true;
}

/**
 * Aller à la frame suivante de la vidéo chargée au sein de la plateforme
 * @brief C_Video::testNext
 */
void C_Video::goToNextFrame()
{
    MainWindow *w = (MainWindow *)parent();

    //on s'assure que le bouton Précédent soit activé dans tous les cas
    w->ui->previousButton->setEnabled(true);

    //on insère la frame suivante dans le Label de la fenêtre
    loadedVideo->next();
    QPixmap image = loadedVideo->getCurrentImage();
    Frame fr = loadedVideo->getCurrentFrame();

    //ajout des particules dans le tableau
    w->addParticles(fr);

    w->viewerUpdate(image);

    //indice courant de frame
    Tools::debugMessage("Indice courant de frame", loadedVideo->getFrameIndex());

    //on désactive le bouton Suivant si nous sommes à la fin de la liste
    if(loadedVideo->getFrameIndex()==loadedVideo->getFramesList().size()-1)
    {
        w->ui->nextButton->setEnabled(false);
    }

}

/**
 * Aller à la frame suivante de la vidéo chargée au sein de la plateforme
 * @brief C_Video::testPrevious
 */
void C_Video::goToPreviousFrame()
{
    MainWindow *w = (MainWindow *)parent();

    //on s'assure que le bouton Suivant soit activé dans tous les cas
    w->ui->nextButton->setEnabled(true);

    //on insère la frame précédente dans le Label de la fenêtre
    loadedVideo->previous();
    QPixmap image = loadedVideo->getCurrentImage();
    Frame fr = loadedVideo->getCurrentFrame();

    //ajout des particules dans la tableau
    w->addParticles(fr);

    w->viewerUpdate(image);

    //indice courant de frame
    Tools::debugMessage("Indice courant de frame", loadedVideo->getFrameIndex());

    //on désactive le bouton Précédent si nous sommes au début de la liste
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

