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
    QList<unsigned int> particleIdSelected_; // List of particle id selected (displayed on the viewer)
    QList<double> particleWeightSelected_; // List of particles weight selected
    bool displayObjects_; // Display Objects if TRUE
    cv::Mat frameMatrix_; // The origin image from the VideoCapture
public:
    Video();
    Video(QString file);
    ~Video();

    /********** GETTER **********/
    QString getFileName();
    QList<Frame> &getFramesList();
    cv::VideoCapture getVideoCapture();
    unsigned int getFramesCount();
    QPixmap getNextImage();
    Frame getCurrentFrame();
    unsigned int getFrameIndex();
    bool isObjectsDisplay();
    cv::Mat getFrameMatrix();
    QPixmap getCurrentImage();
    QList<unsigned int> getParticleIdSelected();

    /********** SETTER **********/
    void setIndex(unsigned int frameIndex);
    void setObjectsDisplay(bool isDisplay);
    void setParticleDisplay(bool isDisplay, unsigned int particleId, double particleWeight);
    void setParticleIdSelected(QList<unsigned int> newParticleIdSelected);
    void setParticleWeightSelected();


    /********** ADDING FUNCTION **********/
    void addFrame(Frame frame);

    /********** NAVIGATION **********/
    void next();
    void previous();
    void setFrame(unsigned int framePosition);


};

#endif // VIDEO_H
