#include "layer.h"

Layer::Layer(int rows, int cols)
{
    graphId_ = -1;
    matrix_.zeros(rows,cols,CV_32F);
}


cv::Mat Layer::getMatrix()
{
    return matrix_;
}

