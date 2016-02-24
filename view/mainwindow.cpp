#include "view/mainwindow.h"

/**
 * Constructor
 * @brief MainWindow::MainWindow
 * @param parent the parent QWidget
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

    /********** TIMER for handling the video read **********/
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

}

/**
 * Destructor
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}


/**********************************************************************/
/*                         INTERFACE FUNCTIONS                        */
/**********************************************************************/

/**
 * Update the label viewer from the mainwindow
 * @brief MainWindow::setFrameIntoLabel
 * @param image the pixmap to update
 */
void MainWindow::viewerUpdate(QPixmap image)
{
    if (!image.isNull())
    {
        // Update the viewer
        ui->viewer->setPixmap(image);
        ui->viewer->adjustSize();
        ui->viewer->show();

        // Update the frame index in the spinbox
        ui->spinBoxFrame->setValue(getVideoController()->getLoadedVideo()->getFrameIndex());
    }
    else
    {
        Tools::debugMessage("Unable to load the video frame");
    }
}

/**
 * Update the particles table
 * @brief MainWindow::addParticles
 * @param frame the frame which contains the particles
 */
void MainWindow::addParticles(Frame frame)
{
    // Clean the particle table
    while (ui->tableParticle->rowCount()>0)
    {
        ui->tableParticle->removeRow(0);
    }
    // Get the particle list
    QList<Particle*> listParticles = frame.getParticlesList();

    // We fill the table with the data if the list isn't empty
    if(!listParticles.isEmpty())
    {
        for (int i=0;i<listParticles.size();i++)
        {
            QTableWidgetItem *idParticle = new QTableWidgetItem(QString().setNum(listParticles.at(i)->getParticleId()));
            QTableWidgetItem *weightParticle = new QTableWidgetItem(QString().setNum(listParticles.at(i)->getWeightParticle()));

            // Unable to edit the data inside the QTableView
            idParticle->setFlags(idParticle->flags() ^ Qt::ItemIsEditable);
            weightParticle->setFlags(weightParticle->flags() ^ Qt::ItemIsEditable);

            // We insert a new row
            ui->tableParticle->insertRow(i);
            ui->tableParticle->setItem(i,ID_PARTICLE_TABLEVIEW,idParticle);
            ui->tableParticle->setItem(i,WEIGHT_PARTICLE_TABLEVIEW,weightParticle);
        }
        // We sort the particle by WEIGHT
        ui->tableParticle->sortByColumn(WEIGHT_PARTICLE_TABLEVIEW);
    }
}

/**
 * Update the particles table
 * @brief MainWindow::addParticles
 * @param frame the frame which contains the particles
 */
void MainWindow::selectParticles(Video* video)
{
    QList<unsigned int> particleIdSelected = video->getParticleIdSelected();
    QList<unsigned int> newParticleIdSelected = QList<unsigned int>();
    if(!particleIdSelected.isEmpty() && particleIdSelected.size() != 0)
    {
        int size = (int)ui->tableParticle->rowCount();
        Tools::debugMessage("Table size",size);
        Tools::debugMessage("Particle list size",particleIdSelected.size());
        if(size > 0)
        {
            for(int i = 0 ; i < size; i++)
            {
                if(particleIdSelected.contains(ui->tableParticle->item(i,ID_PARTICLE_TABLEVIEW)->text().toInt()))
                {
                    Tools::debugMessage("Row selected",ui->tableParticle->item(i,ID_PARTICLE_TABLEVIEW)->text());
                    ui->tableParticle->selectRow(i);
                    newParticleIdSelected.append(ui->tableParticle->item(i,ID_PARTICLE_TABLEVIEW)->text().toInt());
                }
            }
        }
    video->setParticleIdSelected(newParticleIdSelected);
    }
}


/**********************************************************************/
/*                               GETTER                               */
/**********************************************************************/

/**
 * Get the video controller
 * @brief MainWindow::getVideoController
 * @return the video controller
 */
C_Video* MainWindow::getVideoController()
{
    return this->videoController;
}
