#ifndef PARTICLE_H
#define PARTICLE_H

#include <QList>

#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "tools.h"

class Particle
{
private:
    double weightParticle_; // particle weight
protected:
    unsigned int idParticle_; // particle id
public:

    Particle();
    virtual ~Particle();

    /***** GETTER *****/
    double getWeightParticle();
    unsigned int getParticleId();

    /***** SETTER *****/
    void setIdParticle(unsigned particleId);
    void setWeightParticle(double weightParticle);

    /***** DRAWING FUNCTION *****/
    virtual void drawParticle(cv::Mat&,unsigned int,QList<double>){}; // Omit the parameter name because of polymorphism
};

#endif // PARTICLE_H
