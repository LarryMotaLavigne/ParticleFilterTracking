#include <QApplication>
#include <QPushButton>

#include "view/mainwindow.h"

#include "tools.h"

int main(int argc, char *argv[])
{
    //utilisation des fichiers de log pour messages de debug
    qInstallMessageHandler(Tools::customMessageHandler);
    Tools::debugMessage("-----------------------LANCEMENT DE L'APPLICATION-----------------------");

    QApplication a(argc, argv);

    MainWindow w;

    w.show();

    return a.exec();
}
