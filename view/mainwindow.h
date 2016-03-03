#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QObject>
#include <QInputDialog>
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QList>
#include <QStyledItemDelegate>
#include <QPainter>

#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/opencv.hpp>

#include "controller/c_video.h"
#include "controller/c_algorithm.h"

#include "model/frame.h"
#include "model/video.h"
#include "model/particle.h"
#include "tools.h"

#include "helpwindow.h"

#include "ui_mainwindow.h"

class C_Video;
class C_Algorithm;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    C_Video* videoController; // video controller
    C_Algorithm* algoController; // algorithm controller

    HelpWindow* helpWindow; // Help Window
public:
    Ui::MainWindow* ui;    
    QTimer *tmrTimer; // Timer declaration

    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

    /********** INTERFACE FUNCTIONS **********/
    void viewerUpdate(QPixmap image); // Add an image (QPixmap) to a viewer (QLabel)
    void addParticles(Frame frame);   // Add a list of particles in a table for the current frame
    void selectParticles(Video* video); // Refresh the table list with the selected particles

    /********** GETTER **********/
    C_Video* getVideoController();

public slots:
    void openHelpWindow();

};


class BackgroundDelegate : public QStyledItemDelegate
{
public:
    explicit BackgroundDelegate(QObject *parent = 0)
        : QStyledItemDelegate(parent)
    {
    }
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const
    {
        // Fill the background before calling the base class paint
        // otherwise selected cells would have a white background
        QVariant background = index.data(Qt::BackgroundRole);
        if (background.canConvert<QBrush>())
            painter->fillRect(option.rect, background.value<QBrush>());

        QStyledItemDelegate::paint(painter, option, index);

//        // To draw a border on selected cells
//        if(option.state & QStyle::State_Selected)
//        {
//            painter->save();
//            QPen pen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
//            int w = pen.width()/2;
//            painter->setPen(pen);
//            painter->drawRect(option.rect.adjusted(w,w,-w,-w));
//            painter->restore();
//        }
    }
};

#endif // MAINWINDOW_H
