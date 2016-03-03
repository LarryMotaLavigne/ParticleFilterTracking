#ifndef FRAME_H
#define FRAME_H

#include <QObject>
#include <QImage>
#include <QPixmap>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/opencv.hpp>

#include "model/object.h"
#include "model/particle.h"
#include "tools.h"

class Frame
{
private:
    QList<Object> objectsList_; // Objects list from a frame
    QList<Particle*> particlesList_; // Particles list from a frame
    unsigned int frameIndex_; // Index of the frame

public:
    Frame();
    Frame(unsigned int frameIndex);
    Frame(const Frame& other);
    ~Frame();

    /********** GETTER **********/
    QList<Object>& getObjectsList();
    QList<Particle*> getParticlesList();

    Object getObjectByPosition(unsigned int position);
    unsigned int getFrameIndex();
    Particle getParticleByPosition(unsigned int position);

    /********** SETTER **********/
    void setFrameIndex(unsigned int index);

    /***** ADDING FUNCTIONS *****/
    void addObject(Object object);
    void addParticleToFrame(Particle* particle);

    /***** DRAWING FUNCTIONS *****/
    void drawObjects(cv::Mat& img);
    void drawParticle(cv::Mat& img, unsigned int position, unsigned int particleId, QList<double> particleWeightToDisplay);
};

#endif // FRAME_H
