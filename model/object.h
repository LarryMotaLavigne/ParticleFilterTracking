#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>

#include "tools.h"

#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


class Object
{

private:
    unsigned int idObject_; // object id
    cv::Point leftTopPoint_; // LEFT TOP point of the object detection rectangle
    cv::Point rightBottomPoint_; // RIGHT BOTTOM point of the object detection rectangle

public:
    Object();
    Object(unsigned int idObject, cv::Point leftTopPoint, cv::Point rightBottomPoint);
    ~Object();

    /********** GETTER *********/
    unsigned int getIdObject();
    cv::Point getLeftTopPoint();
    cv::Point getRightBottomPoint();

    /******** DRAWING FUNCTION ********/
    void drawObject(cv::Mat& img);

};

#endif // OBJECT_H
