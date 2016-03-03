#include <QApplication>
#include <QPushButton>

#include "view/mainwindow.h"

#include "tools.h"

int main(int argc, char *argv[])
{
    // Using log file to handle debug messages
    qInstallMessageHandler(Tools::customMessageHandler);
    Tools::debugMessage("----------------------- RUNNING THE APP -----------------------");
    Tools::configuration();

    QApplication a(argc, argv);

    MainWindow w;

    w.show();

    return a.exec();
}
