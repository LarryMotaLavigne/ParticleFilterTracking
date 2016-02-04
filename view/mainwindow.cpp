#include "view/mainwindow.h"


/**
 * Constructor
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    videoController = new C_Video(this); // Video Controller Initialization
    algoController = new C_Algorithm(this); // Algorithm Controller Initialization

    // All button are disabled at first except the button used for opening the video
    ui->action_openAlgorithm->setEnabled(false);
    ui->boutonRevenirDebut->setEnabled(false);
    ui->previousButton->setEnabled(false);
    ui->previousButton->setShortcut(Qt::Key_Left);
    ui->nextButton->setEnabled(false);
    ui->nextButton->setShortcut(Qt::Key_Right);
    ui->playButton->setEnabled(false);
    ui->playButton->setShortcut(Qt::Key_Space);

    /********** TIMER pour la gestion de la lecture vidéo **********/
    tmrTimer = new QTimer(this);
    connect(tmrTimer, SIGNAL(timeout()), videoController, SLOT(readVideo()));

    /********** SLOT & SIGNAL **********/
    connect(ui->action_openVideo, SIGNAL(triggered()), videoController, SLOT(openVideo()));
    connect(ui->action_openAlgorithm, SIGNAL(triggered()), algoController, SLOT(openAlgorithm()));
    connect(ui->boutonRevenirDebut, SIGNAL(clicked()), videoController, SLOT(returnToFirstFrame()));
    connect(ui->nextButton, SIGNAL(clicked()), videoController, SLOT(goToNextFrame()));
    connect(ui->previousButton, SIGNAL(clicked()), videoController, SLOT(goToPreviousFrame()));
    connect(ui->playButton, SIGNAL(clicked()), videoController, SLOT(startOrStopTimer()));
    connect(ui->objectsDisplayBox, SIGNAL(clicked()), videoController, SLOT(displayObjects()));
    connect(ui->tableParticle, SIGNAL(itemClicked(QTableWidgetItem*)),videoController,SLOT(displayGraphs(QTableWidgetItem*)));

    //gestion du spinBoxFrame
    //connect(ui->spinBoxFrame,SIGNAL(valueChanged(int)), videoController, SLOT(goToSpecificFrame()));
    //gestion du tableau des particules


}

/**
 * Mise à jour du contenu du Label de la fenêtre principale
 * @brief MainWindow::setFrameIntoLabel
 * @param image
 */
void MainWindow::viewerUpdate(QPixmap image)
{
    if (!image.isNull())
    {
        //mise à jour du contenu du Label
        ui->viewer->setPixmap(image);
        ui->viewer->adjustSize();
        ui->viewer->show();
        //mise à jour du numéro de frame
        ui->spinBoxFrame->setValue(getVideoController()->getLoadedVideo()->getFrameIndex());
    }
    else
    {
        Tools::debugMessage("Probleme de chargement de la frame de la video : NULL FRAME");
    }
}

/**
 * Remplissage du tableau des particules au sein de l'application
 * @brief MainWindow::addParticles
 * @param frame
 */
void MainWindow::addParticles(Frame frame)
{

    //On efface les lignes déjà présentes dans la table
    while (ui->tableParticle->rowCount()>0)
    {
        ui->tableParticle->removeRow(0);
    }

    //on récupère la liste des particules de la frame en cours
    QList<Particle*> listParticles = frame.getParticlesList();

    //si la liste des particules n'est pas vide, on remplit la QTableView avec
    if(!listParticles.isEmpty())
    {
        for (int i=0;i<listParticles.size();i++)
        {
            QTableWidgetItem *idParticle = new QTableWidgetItem(QString::number(i));
            QTableWidgetItem *weightParticle = new QTableWidgetItem(QString().setNum(listParticles.at(i)->getWeightParticle()));

            //rend l'édition des données au sein de la QTableView impossible
            idParticle->setFlags(idParticle->flags() ^ Qt::ItemIsEditable);
            weightParticle->setFlags(weightParticle->flags() ^ Qt::ItemIsEditable);

            //*
            ui->tableParticle->insertRow(i);
            ui->tableParticle->setItem(i,0,idParticle);
            ui->tableParticle->setItem(i,1,weightParticle);
            /* */
        }
        ui->tableParticle->sortByColumn(1);
    }
}


/**
 * Le destructeur
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}
