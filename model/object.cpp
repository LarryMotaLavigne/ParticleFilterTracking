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
    cv::Mat temp = img.clone();

    cv::Rect rect(leftTopPoint_, rightBottomPoint_);
    cv::rectangle(temp,rect,cv::Scalar(255,0,0),-1); // Blue (255,0,0) Green(0,255,0) Red(0,0,255)
    double alpha = 0.3;
    cv::addWeighted(temp,alpha,img,1.0-alpha,0.0,img);

    /* LABEL */
    QString idObjectStr = QString::number(idObject_);
    Tools::setLabel(img,rect,idObjectStr);
}

