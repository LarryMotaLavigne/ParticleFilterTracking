#include "model/particle.h"

/**
 * Default constructor
 * @brief Particle::Particle
 */
Particle::Particle()
{

}

/**
 * Destructor
 * @brief Particle::~Particle
 */
Particle::~Particle()
{

}


/**********************************************************************/
/*                               GETTER                               */
/**********************************************************************/

/**
 * Get the particle weight
 * @brief Particle::getWeightParticle
 * @return weightParticule_ the particle weight
 */
double Particle::getWeightParticle()
{
    return weightParticle_;
}

unsigned int Particle::getParticleId()
{
    return idParticle_;
}

/**********************************************************************/
/*                               SETTER                               */
/**********************************************************************/

/**
 * Set the particle weight
 * @brief Particle::setWeightParticle
 * @param weightParticle the weight to set²
 */
void Particle::setWeightParticle(double weightParticle)
{
    this->weightParticle_ = weightParticle;
}

/**
 * Set the particle id
 * @brief Particle::setIdParticle
 * @param idParticle the id of the particle
 */
void Particle::setIdParticle(unsigned idParticle)
{
    this->idParticle_ = idParticle;
}
