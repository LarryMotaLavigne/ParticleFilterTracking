#include "model/frame.h"

/**
 * Default constructor
 * @brief Frame::Frame
 */
Frame::Frame()
{

}

/**
 * Destructor
 * @brief Frame::~Frame
 */
Frame::~Frame()
{

}

/**
 * Constructor
 * @brief Frame::Frame
 * @param frameIndex the index of the specific frame
 */
Frame::Frame(unsigned int frameIndex)
{
    this->frameIndex_ = frameIndex;
}

/**
 * Copy constructor
 * @brief Frame::Frame
 * @param other the frame to copy
 */
Frame::Frame(const Frame& other)
{
    this->objectsList_ = other.objectsList_;
    this->particlesList_ = other.particlesList_;
    this->frameIndex_ = other.frameIndex_;
}



/**********************************************************************/
/*                               GETTER                               */
/**********************************************************************/

/**
 * Get object list
 * @brief Objet::getObjectsList
 * @return objectsList_ the list of the objects
 */
QList<Object> &Frame::getObjectsList()
{
    return objectsList_;
}

/**
 * Get a specific object with his position in the list
 * @brief Frame::getObjectByPosition
 * @param position the position in the list of the object
 * @return result the object
 */
Object Frame::getObjectByPosition(unsigned int position)
{
    return objectsList_[position];
}

/**
 * Get the index of the frame
 * @brief Frame::getIndiceFrame
 * @return frameIndex_ the index of the frame
 */
unsigned int Frame::getFrameIndex()
{
    return frameIndex_;
}

/**
 * Get the particles list from a frame
 * @brief Frame::getParticlesList
 * @return particlesList_ the particles list
 */
QList<Particle*> Frame::getParticlesList()
{
    return particlesList_;
}


/**
 * Get the particle in the list at a specific position
 * @brief Frame::getParticleByPosition
 * @param position the position of the particle in the list
 * @return result the particle
 */
Particle Frame::getParticleByPosition(unsigned int position)
{
    return *particlesList_[position];
}


/**********************************************************************/
/*                               SETTER                               */
/**********************************************************************/

/**
 * Set the frame index
 * @brief Frame::setFrameIndex
 * @param index the new frame index
 */
void Frame::setFrameIndex(unsigned int index)
{
    frameIndex_ = index;
}



/**********************************************************************/
/*                          ADDING FUNCTIONS                          */
/**********************************************************************/

/**
 * Add an object to a frame
 * @brief Frame::addObject
 * @param obj the object to add
 */
void Frame::addObject(Object object)
{
    objectsList_.append(object);
}

/**
 * Add a particle to the frame
 * @brief Frame::addParticleToFrame
 * @param particle the particle to add
 */
void Frame::addParticleToFrame(Particle* particle)
{
    particlesList_.append(particle);
}

/**********************************************************************/
/*                          DRAWING FUNCTIONS                         */
/**********************************************************************/

/**
 * Draw all the objects of the specific frame
 * @brief Frame::drawObjects
 * @param img the image
 */
void Frame::drawObjects(cv::Mat& img)
{
    for (int i=0;i<objectsList_.size();i++)
    {
        this->objectsList_[i].drawObject(img);
    }
}

/**
 * Draw all the particles of the specific frame
 * @brief Frame::drawParticles
 * @param img the image
 */
void Frame::drawParticles(cv::Mat& img)
{
    for (int i=0;i<particlesList_.size();i++)
    {
        particlesList_[i]->drawParticle(img);
    }
}


/**
 * Draw a single particle of the specific frame
 * @brief Frame::drawParticle
 * @param img the image
 * @param particleId the particle id
 */
void Frame::drawParticle(cv::Mat& img, unsigned int particleId)
{
    for (int i = 0; i < particlesList_.size(); ++i)
    {
        if(particlesList_[i]->getParticleId() == particleId)
            particlesList_[i]->drawParticle(img);
    }
}

