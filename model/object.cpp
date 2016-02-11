#include "model/object.h"

/**
 * Default constructor
 * @brief Object::Object
 */
Object::Object()
{

}

/**
 * Constructor
 * @brief Object::Object
 * @param idObject the object id
 * @param leftTopPoint the LEFT TOP point of the object detection rectangle
 * @param rightBottomPoint the RIGHT BOTTOM point of the object detection rectangle
 */
Object::Object(unsigned int idObject, cv::Point leftTopPoint, cv::Point rightBottomPoint)
{
    this->idObject_ = idObject;
    this->leftTopPoint_ = leftTopPoint;
    this->rightBottomPoint_ = rightBottomPoint;
}



/**
 * Destructor
 * @brief Object::~Object
 */
Object::~Object()
{

}


/**********************************************************************/
/*                               GETTER                               */
/**********************************************************************/

/**
 * Get the object id
 * @brief Object::getIdObjet
 * @return the object id
 */
unsigned int Object::getIdObject()
{
    return this->idObject_;
}

/**
 * Get the LEFT TOP point of the object detection rectangle
 * @brief Object::getLeftTopPoint
 * @return the LEFT TOP point of the object detection rectangle
 */
cv::Point Object::getLeftTopPoint()
{
    return this->leftTopPoint_;
}

/**
 * Get the RIGHT BOTTOM point of the object detection rectangle
 * @brief Object::getRightBottomPoint
 * @return the RIGHT BOTTOM point of the object detection rectangle
 */
cv::Point Object::getRightBottomPoint()
{
    return this->rightBottomPoint_;
}


/**********************************************************************/
/*                          DRAWING FUNCTION                          */
/**********************************************************************/

/**
 * Draw the object on the image
 * @brief Object::drawObject
 * @param img the image
 */
void Object::drawObject(cv::Mat& img)
{
    /* RECTANGLE */
    cv::Rect rRect(leftTopPoint_, rightBottomPoint_);
    cv::rectangle(img,rRect,cv::Scalar(255,0,0)); // Couleur bleu(255,0,0) vert(0,255,0) rouge (0,0,255)

    /* LABEL */
    QString idObjectStr = QString::number(idObject_);
    Tools::setLabel(img,rRect,idObjectStr);
}

