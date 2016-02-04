#ifndef TOOLS_H
#define TOOLS_H

#include <QObject>
#include <QImage>
#include <QPixmap>

#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/opencv.hpp>




class Tools
{
public:
    Tools();
    ~Tools();

    /********* DEBUG **********/
    static void debugMessage(QString message);
    static void debugMessage(QString message, bool value);
    static void debugMessage(QString message, int value);
    static void debugMessage(QString message, unsigned int value);
    static void debugMessage(QString message, QString value);
    static void debugMessage(QString message, double value);

    /********* LOGS write **********/
    static void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

    /********* CONVERSION **********/
    static QPixmap cvMatToQPixmap( const cv::Mat &inMat );
    static QImage cvMatToQImage( const cv::Mat &inMat );

    // Writing label into a cv::rectangle on the current image
    static void setLabel(cv::Mat& im, cv::Rect r, QString label);

};

#endif // TOOLS_H
