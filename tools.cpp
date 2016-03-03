#include "tools.h"

/********* GLOBAL VARIABLE INIT **********/
int Tools::idParticleTableview = 0;
int Tools::weightParticleTableView = 1;
int Tools::maxParticleDisplay = 5;
cv::Scalar Tools::objectColor = CV_RGB(0,255,0);
cv::Scalar Tools::labelColor = CV_RGB(0,255,0);
cv::Scalar Tools::particleColor = CV_RGB(0,0,255);
int Tools::edgeThickness = 2;
int Tools::rectangleThickness = -1;
QList<cv::Scalar> Tools::colorList({CV_RGB(255,0,0),CV_RGB(255,127,0),CV_RGB(255,255,0),CV_RGB(127,255,0),CV_RGB(0,255,0),CV_RGB(0,255,127),CV_RGB(0,255,255),CV_RGB(0,127,255),CV_RGB(0,0,255),CV_RGB(127,0,255),CV_RGB(255,0,255),CV_RGB(255,0,127)});


/**
 * Constructor
 * @brief Tools::Tools
 */
Tools::Tools()
{

}

/**
 * Destructor
 * @brief Tools::~Tools
 */
Tools::~Tools()
{

}


/**
 * Get configuration properties from the config file
 * @brief Tools::configuration
 */
void Tools::configuration()
{
    debugMessage("Configuration");
    // Get info from file configuration.conf

    QFile file("configuration.conf");
    if(!file.open(QIODevice::ReadOnly)) {
        debugMessage("Error",file.errorString());
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        debugMessage("CONF",line);

        QStringList fields = line.split(" ");
        if(fields.at(0) == "idParticleTableview")
        {
            idParticleTableview = fields.at(1).toInt();
        }
        else if(fields.at(0) == "weightParticleTableView")
        {
            weightParticleTableView = fields.at(1).toInt();
        }
        else if(fields.at(0) == "maxParticleDisplay")
        {
            maxParticleDisplay = fields.at(1).toInt();
        }
        else if(fields.at(0) == "edgeThickness")
        {
            edgeThickness = fields.at(1).toInt();
        }
        else if(fields.at(0) == "rectangleThickness")
        {
            rectangleThickness = fields.at(1).toInt();
        }
        else if(fields.at(0) == "objectColor")
        {
            objectColor = CV_RGB(fields.at(1).toInt(),fields.at(2).toInt(),fields.at(3).toInt());
        }
        else if(fields.at(0) == "labelColor")
        {
            labelColor = CV_RGB(fields.at(1).toInt(),fields.at(2).toInt(),fields.at(3).toInt());
        }
        else if(fields.at(0) == "particleColor")
        {
            particleColor = CV_RGB(fields.at(1).toInt(),fields.at(2).toInt(),fields.at(3).toInt());
        }

    }

    file.close();
}


/**
 * Simple debug message
 * @brief Tools::debugMessage
 * @param message the message to display
 */
void Tools::debugMessage(QString message)
{
    qDebug("%s", message.toStdString().c_str());
}

/**
 * Debug message with boolean value
 * @brief Tools::debugMessage
 * @param message the message to display
 * @param value the boolean value
 */
void Tools::debugMessage(QString message, bool value)
{
    qDebug("%s : %s", message.toStdString().c_str(),value ? "True" : "False");
}

/**
 * Debug message with integer value
 * @brief Tools::debugMessage
 * @param message the message to display
 * @param value the integer value
 */
void Tools::debugMessage(QString message, int value)
{
    qDebug("%s : %d", message.toStdString().c_str(),value);
}

/**
 * Debug message with uint value
 * @brief Tools::debugMessage
 * @param message the message to display
 * @param value the uint value
 */
void Tools::debugMessage(QString message, unsigned int value)
{
    qDebug("%s : %d", message.toStdString().c_str(),value);
}

/**
 * Debug message with Qt message
 * @brief Tools::debugMessage
 * @param message the message to display
 * @param value the qtmessage
 */
void Tools::debugMessage(QString message, QString value)
{
    qDebug("%s : %s", message.toStdString().c_str(),value.toStdString().c_str());
}

/**
 * Debug message with double value
 * @brief Tools::debugMessage
 * @param message the message to display
 * @param value the double value
 */
void Tools::debugMessage(QString message, double value)
{
    qDebug("%s : %f", message.toStdString().c_str(),value);
}

/**
 * Write message in the log file
 * @brief Tools::customMessageHandler
 * @param type
 * @param context
 * @param msg
 */
void Tools::customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context);

    QString dateTime = QDateTime::currentDateTime().toString("hh:mm:ss");
    QString txt = QString("[%1] ").arg(dateTime);

    switch (type)
    {
        case QtDebugMsg:
            txt += QString("{Debug} \t\t %1").arg(msg);
            break;
        case QtWarningMsg:
            txt += QString("{Warning} \t %1").arg(msg);
            break;
        case QtCriticalMsg:
            txt += QString("{Critical} \t %1").arg(msg);
            break;
        case QtFatalMsg:
            txt += QString("{Fatal} \t\t %1").arg(msg);
            abort();
            break;
    }

    dateTime = QDateTime::currentDateTime().toString("dd_MM_yyyy");

    //Configuration of the log file (LogFile_[currentDate].log)
    QString filenameToCreate = "LogFile_" + dateTime + ".log";
    QFile outFile(filenameToCreate);

    // Open the file (in Writing mode only, or in Append mode)
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);

    // Writing in the log file
    QTextStream textStream(&outFile);
    textStream << txt << endl;

    // Writing in the console
    std::cout << txt.toStdString() << std::endl;

}

/**
 * Convert cv:Mat image into a QPixmap
 * @brief Tools::cvMatToQPixmap
 * @param inMat
 * @return image the QPixmap object
 */
QPixmap Tools::cvMatToQPixmap( const cv::Mat &inMat )
{
    return QPixmap::fromImage( cvMatToQImage( inMat ) );
}

/**
 * Convert cv:Mat image into a QImage
 * @brief Tools::cvMatToQImage
 * @param inMat
 * @return image the QImage object
 */
QImage Tools::cvMatToQImage( const cv::Mat &inMat )
{
    switch ( inMat.type() )
    {
        // 8-bit, 4 channel
        case CV_8UC4:
        {
            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32 );
            return image;
        }

        // 8-bit, 3 channel
        case CV_8UC3:
        {
            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );
            return image.rgbSwapped();
        }

        // 8-bit, 1 channel
        case CV_8UC1:
        {
            static QVector<QRgb>  sColorTable;

            // only create our color table once
            if ( sColorTable.isEmpty() )
            {
                for ( int i = 0; i < 256; ++i )
                    sColorTable.push_back( qRgb( i, i, i ) );
            }

            QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8 );
            image.setColorTable( sColorTable );
            return image;
        }

        default:
            break;
    }

    return QImage();
}

/**
 * Display the label boxes into a cv:Mat
 * @brief set_label
 * @param im
 * @param r
 * @param label
 */
void Tools::setLabel(cv::Mat& im, cv::Rect r, QString label)
{
    int fontface = cv::FONT_HERSHEY_SCRIPT_COMPLEX;
    double scale = 0.5;
    int thickness = 0.5;

    //cv::Point pt(r.x + (r.width-text.width)/2, r.y + (r.height+text.height)/2);
    cv::Point pt(r.x,r.y - 5);

    cv::putText(im, label.toStdString(), pt, fontface, scale, Tools::labelColor, thickness, 8);
}
