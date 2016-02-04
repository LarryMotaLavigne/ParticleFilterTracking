#ifndef C_ALGORITHM_H
#define C_ALGORITHM_H

#include <QObject>
#include <QMap>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QDirIterator>

#include "model/frame.h"
#include "model/object.h"
#include "model/graph.h"
#include "model/node.h"
#include "controller/c_video.h"

#include <opencv/cv.h>
#include "tools.h"
#include "view/mainwindow.h"

class C_Algorithm : public QObject
{
    Q_OBJECT
public:
    C_Algorithm(QObject *parent = NULL);
    ~C_Algorithm();

    QStringList objectList_;   // list which contain the file : <videoName>.txt
    QStringList frameHypList_; // list which contain the file : FrameHyp<numFrame>.txt
    QStringList graphList_;    // list which contain the file : Graph<numFrame>_<numParticle>.txt

    void displayObjectList();
    void displayFrameHypList();
    void displayGrapheList();

    QMap<QString,double> map; // QMap which associate a Weight to a Graph

public slots :
    bool openAlgorithm(); // Opening of the algorithm files
    bool createObject(QString str);    // Handle the <videoName>.txt file
    bool createGraph(QString str);     // Handle the Graph<numFrame>_<numParticle>.txt file
    bool createFrameHyp(QString str);  // Handle the FrameHyp<numFrame>.txt file

};

#endif // C_ALGORITHM_H
