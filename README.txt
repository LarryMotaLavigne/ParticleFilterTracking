=======================================================================================
Bienvenue sur la plateforme A.T.A.S (Algorithm Tracking Analysis Software)
=======================================================================================

A.T.A.S est une plateforme développée dans le cadre d'un Projet de Fin d'Étude
de Cycle Ingénieur par Benjamin Ferré en 2015, étudiant à l'École Polytechnique
Universitaire de Tours. Ce projet a été encadré par Monsieur Donatello Conte, enseignant
chercheur à l'École Polytechnique Universitaire de Tours.

Développeur : Benjamin Ferré (benjamin.ferre@etu.univ-tours.fr)
Date de rédaction Readme.txt : 08 Mai 2015

Encadrant : Donatello Conte (donatello.conte@univ-tours.fr)

---------------------------------------------------------------------------------------
Objectif de la plateforme
---------------------------------------------------------------------------------------

La plateforme est conçue pour visualiser des résultats d'algorithmes implémentant
des solutions de suivi d'objets. A partir d'une vidéo importée dans la plateforme
et des fichiers de résultats obtenus par l'exécution de l'algorithme sur cette même
vidéo, la plateforme permet l'affichage des objets et des hypothèses de visualisation.

---------------------------------------------------------------------------------------
Outils de développement
---------------------------------------------------------------------------------------

Dans le cadre du développement de cette plateforme, les outils ayant été utilisés
sont :
- QtCreator Community 3.3.0
- Compilateur MinGW 4.9.1 32 bits
- Bibliothèque OpenCV 2.4.10.0 compilée avec CMake 3.1.0

---------------------------------------------------------------------------------------
Configuration minimale pour utilisation
---------------------------------------------------------------------------------------

- Système d'exploitation : Microsoft Windows
- Mémoire vive minimum : 2.00 Go
- Carte graphique : mémoire vive 1.00 Go

---------------------------------------------------------------------------------------
Utilisation de la plateforme
---------------------------------------------------------------------------------------

1) Cliquer sur l'exécutable ATAS.exe pour démarrer l'application
2) Pour effectuer l'importation d'une vidéo au sein de la plateforme :
	- Dans le menu Visualisation, cliquer sur Ouvrir une Vidéo ;
	- Sélectionner la vidéo à importer 
		Formats actuellement acceptés : .avi .mov .mpg .mp4 .asf
3) Une fois la vidéo importée, les options de visualisation sont disponibles : 
Lecture/Pause, Avancer d'une frame, Reculer d'une frame, Revenir au début, 
Aller à la frame (sélection par numéro de frame)
4) Pour effectuer l'importation d'un algorithme au sein de la plateforme :
	- Dans le menu Visualisation, cliquer sur Ouvrir un algorithme ;
	- Sélectionner le dossier dans lequel se situent les fichiers de sortie de 
	l'algorithme.
		Voir structure de fichiers acceptés à la section "Structure des fichiers" 
		du présent document.
5) Une fois l'algorithme importé, les options de visualisation des objets et des
hypothèses sont disponibles. L'affichage des objets se fait pa défaut sur chaque frame.
L'affichage des hypothèses s'active en sélectionnant les hypothèses souhaitées dans le
tableau de donnéesde l'application.

---------------------------------------------------------------------------------------
Sources du programme - Classes 
---------------------------------------------------------------------------------------
Classes Modèle
	> video.h et video.cpp : classe définissant l'objet Video suite à importation d'une 
	vidéo
	> frame.h et frame.cpp : classe définissant les objets Frame composant l'objet Video
	> objet.h et objet.cpp : classe définissant les objets contenus dans les frmaes et
	définis au sein des fichiers de résultats d'algorithme importés
	> graphe.h et graphe.cpp : classe définissant les graphes de scène des frames de la 
	vidéo suite à importation des des fichiers de résultats d'algorithme
	> node.h et node.cpp : classe définissant les noeuds des graphes
	> edge.h et edge.cpp : classe définissant les arcs des graphes
	> frameparticule.h et frameparticule.cpp : classe permettant d'associer à un graphe
	un poids

Classes Vue
	> mainwindow.h et mainwindow.cpp : classe définissant les éléments de vue de la 
	fenêtre principale
	> mainwindow.ui : document au format XML rassemblant les éléments de vue de la 
	fenêtre définis via l'utilisation de QtDesigner

Classes Contrôleur
	> c_video.h et c_video.cpp : classe définissant le contrôleur Vidéo, pour les actions
	d'importation et de lecture
	> c_algorithm.h et c_algorithm.cpp : classe définissant le contrôleur Algorithm, pour 
	les actions d'importation de fichiers et de visualisation des objets et hypothèses

---------------------------------------------------------------------------------------
Structure des fichiers
---------------------------------------------------------------------------------------

Pour pouvoir importer des résultats d'algorithme au sein de la plateforme, les
fichiers de données doivent avoir la structure suivante :

***************FICHIER FRAME (1 fichier pour toute la vidéo)***************

Nom du fichier : Video

Frame <N°Frame>
<id objet> <leftCoord> <topCoord> <rightCoord> <bottomCoord>  
<id objet> <leftCoord> <topCoord> <rightCoord> <bottomCoord>
.
.
.
Frame <N°Frame + 1>
<id objet> <leftCoord> <topCoord> <rightCoord> <bottomCoord>

/*
<id objet> : numero de l'objet détecté
<topCoord> : coordonnée 'haute' du cadre de détection
<bottomCoord> : coordonnée 'basse' du cadre de détection
<leftCoord> : coordonnée 'gauche' du cadre de détection
<rightCoord> : coordonnée 'droite' du cadre de détection
*/

***************FICHIER HYPOTHESE (N fichiers hypothèses)***************

Nom du fichier : FrameHyp <Numero de frame>

<nom du fichier de graphe> <poids>
<nom du fichier de graphe> <poids>
.
.
.
<nom du fichier de graphe> <poids>

/*
<nom du fichier de graphe> : K particules = K fichiers de graphe
<poids> : probabilité associée à la particule
*/

***************FICHIER GRAPHE***************

Nom du fichier : Graphe <Numero de frame>_<Numero de graphe>

<nombreNodes>
<idNode> <labelObjet> <positionX> <positionY> <dimensionLargeur> <dimensionHauteur> <isVisible>
	<nombreEdges> 
	<idNoeudDestination> <poids>
	<idNoeudDestination> <poids>
	...
<idNode> <labelObjet> <positionX> <positionY> <dimensionLargeur> <dimensionHauteur> <isVisible>
.
.
.
<id node> <label objet> <positionX> <positionY> <dimensionLargeur> <dimensionHauteur> <isVisible>

/*
NODES : Noeuds appartenant aux graphes
<idNode> : id du noeud
<labelObjet> : label de l'objet détecté
<positionX> <positionY> : coordonnées de l'objet
<dimensionLargeur> : largeur de l'objet
<dimensionHauteur> : hauteur de l'objet
<isVisible> : booléen informant de la visibilité (ou non) de l'objet considéré

<nombreNodes> : nombre de noeuds dans le graphe
<nombreEdges> : nombre d'arcs issus d'un noeud considéré
*/