#ifndef VIDEO_H
#define VIDEO_H

#include <QObject>
#include <QList>
#include <QFileInfo>

#include "model/frame.h"
#include "tools.h"



class Video
{
private:
    QString filename_; // Name of the video file
    QList<Frame> framesList_; // Frames list of the video
    cv::VideoCapture cap_; // VideoCapture object from which we get the video image
    unsigned int currentFrameIndex_; // index of the current frame
    QList<unsigned int> graphIdToDisplay_;
    bool displayObjects_;
    cv::Mat frameMatrix_;
public:
    Video();
    Video(QString file);
    ~Video();

    /********** GETTER **********/
    QString getFileName();
    QList<Frame> &getFramesList();
    cv::VideoCapture getVideoCapture();
    unsigned int getFramesCount();
    QPixmap getCurrentImage();
    Frame getCurrentFrame();
    unsigned int getFrameIndex();
    bool isObjectsDisplay();
    cv::Mat getFrameMatrix();
    QPixmap refreshCurrentImage();

    /********** SETTER **********/
    void setIndex(unsigned int frameIndex);
    void setObjectsDisplay(bool isDisplay);
    void setGraphDisplay(bool isDisplay, unsigned int graphId);



    /********** ADDING FUNCTION **********/
    void addFrame(Frame frame);

    /********** NAVIGATION **********/
    void next();
    void previous();
    void setFrame(unsigned int framePosition);


};

#endif // VIDEO_H
