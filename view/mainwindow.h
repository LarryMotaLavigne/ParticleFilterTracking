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
    C_Video* videoController; // video controller
    C_Algorithm* algoController; // algorithm controller

public:
    Ui::MainWindow* ui;    
    QTimer *tmrTimer; // Timer declaration

    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

    /********** INTERFACE FUNCTIONS **********/
    void viewerUpdate(QPixmap image); // Add an image (QPixmap) to a viewer (QLabel)
    void addParticles(Frame frame);   // Add a list of particles in a table for the current frame
    void selectParticles(Video* video); // Refresh the table list with the selected particles

    /********** GETTER **********/
    C_Video* getVideoController();

};

#endif // MAINWINDOW_H
