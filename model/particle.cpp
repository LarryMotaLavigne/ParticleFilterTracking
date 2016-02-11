#include "model/particle.h"

/**
 * Default constructor
 * @brief FrameParticule::FrameParticule
 */
Particle::Particle()
{

}

/**
 * Destructor
 * @brief FrameParticule::~FrameParticule
 */
Particle::~Particle()
{

}


/**********************************************************************/
/*                               GETTER                               */
/**********************************************************************/

/**
 * Get the particle weight
 * @brief FrameParticule::getWeightParticle
 * @return weightParticule_ the particle weight
 */
double Particle::getWeightParticle()
{
    return weightParticle_;
}

unsigned int Particle::getParticleId()
{
    return particleId_;
}

/**********************************************************************/
/*                               SETTER                               */
/**********************************************************************/

/**
 * Set the particle weight
 * @brief FrameParticule::setWeightParticle
 * @param weightParticle the weight to set²
 */
void Particle::setWeightParticle(double weightParticle)
{
    weightParticle_ = weightParticle;
}
