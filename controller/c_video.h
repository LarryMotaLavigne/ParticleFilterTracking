#ifndef C_VIDEO_H
#define C_VIDEO_H

#include <QObject>
#include <QDebug>
#include <QFileDialog>
#include <QTableWidgetItem>

#include "view/mainwindow.h"

#include "model/video.h"

class C_Video : public QObject
{
    Q_OBJECT
private :
    Video *loadedVideo;
public:
    C_Video(QObject *parent = NULL);
    ~C_Video();

    Video* getLoadedVideo(){return this->loadedVideo;} //retourne la vidéo chargée

public slots :
    /********* TIMER *********/
    void startOrStopTimer(); //Démarrer ou arrêter le Timer

    /********* OPEN/READ *********/
    void readVideo(); //Lire la vidéo
    bool openVideo(); //Ouvrir la vidéo

    /********* FRAME *********/
    void goToNextFrame(); //Aller à la frame suivante
    void goToPreviousFrame(); //Aller à la frame précédente
    void goToSpecificFrame(); //Aller à une frame spécifique
    void returnToFirstFrame(); //Retourner à la première frame de la vidéo

    /********* ELEMENTS *********/
    void displayObjects(); // Affiche l'ensemble des objets sur la frame en cours
    void displayGraphs(QTableWidgetItem *item);


};

#endif // C_VIDEO_H
