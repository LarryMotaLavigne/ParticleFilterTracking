#ifndef PARTICULE_H
#define PARTICULE_H

#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class Particle
{
private:
    double weightParticle_; // particle weight
protected:
    unsigned int particleId_; // the particle id
public:

    Particle();
    virtual ~Particle();

    /***** GETTER *****/
    double getWeightParticle();
    unsigned int getParticleId();
    /***** SETTER *****/
    void setWeightParticle(double weightParticle);

    /***** DRAWING FUNCTION *****/
    virtual void drawParticle(cv::Mat&){}; // Omit the parameter name because of polymorphism
};

#endif // PARTICULE_H
