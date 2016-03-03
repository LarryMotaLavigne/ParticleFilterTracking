#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QDialog>
#include "tools.h"

#include <QLabel>

namespace Ui {
class HelpWindow;
}

class HelpWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HelpWindow(QWidget *parent = 0);
    ~HelpWindow();

private:
    Ui::HelpWindow *ui;

    void setParticleColor(QLabel* label, cv::Scalar scalar);
};

#endif // HELPWINDOW_H
