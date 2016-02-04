#ifndef LAYER_H
#define LAYER_H

#include <opencv2/opencv.hpp>

class Layer
{
    int graphId_;
    cv::Mat matrix_;
public:
    Layer(int rows, int cols);

    cv::Mat getMatrix();
};

#endif // LAYER_H
