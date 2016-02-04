#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QObject>
#include <QInputDialog>
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QList>


#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/opencv.hpp>

#include "controller/c_video.h"
#include "controller/c_algorithm.h"

#include "model/frame.h"
#include "model/video.h"
#include "model/particle.h"


#include "tools.h"


#include "ui_mainwindow.h"

class C_Video;
class C_Algorithm;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    C_Video* videoController; // Controller video
    C_Algorithm* algoController; // Controller algorithm

public:
    Ui::MainWindow* ui;

    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

    void viewerUpdate(QPixmap image); //Affectation d'une image au QLabel
    void addParticles(Frame frame); //Ajouter les particules dans la tableView

    QTimer *tmrTimer; //déclaration du Timer en public pour faciliter son utilisation

    C_Video* getVideoController(){return this->videoController;} //obtention de l'instance de VideoController

};

#endif // MAINWINDOW_H
