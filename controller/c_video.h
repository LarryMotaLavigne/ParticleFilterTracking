#ifndef C_VIDEO_H
#define C_VIDEO_H

#include <QObject>
#include <QDebug>
#include <QFileDialog>
#include <QTableWidgetItem>

#include "view/mainwindow.h"

#include "model/video.h"

class C_Video : public QObject
{
    Q_OBJECT
private :
    Video *loadedVideo;
public:
    C_Video(QObject *parent = NULL);
    ~C_Video();

    Video* getLoadedVideo();

public slots :
    /********* TIMER *********/
    void startOrStopTimer(); //Start or Stop the timer

    /********* OPEN/READ *********/
    void readVideo();
    bool openVideo();

    /********* FRAME *********/
    void goToNextFrame();
    void goToPreviousFrame();
    void goToSpecificFrame();
    void returnToFirstFrame();

    /********* DISPLAY *********/
    void displayObjects(); // Display the object on the current frame
    void displayGraphs(QTableWidgetItem *item); // Display a graph according the selected item


};

#endif // C_VIDEO_H
