#include "controller/c_algorithm.h"

/**
 * Constructor
 * @brief C_Algorithm::C_Algorithm
 * @param parent the parent object
 */
C_Algorithm::C_Algorithm(QObject *parent) : QObject(parent)
{

}

/**
 * Destructor
 * @brief C_Algorithm::~C_Algorithm
 */
C_Algorithm::~C_Algorithm()
{

}

/**
 * Select and import files
 * @brief C_Algorithm::openAlgorithm
 * @return
 */

bool C_Algorithm::openAlgorithm()
{
    MainWindow *w = (MainWindow *)parent();

    //==================================================================================================================
    //== FILE SELECTION ==
    //==================================================================================================================
    Tools::debugMessage("Opening Algorithm importation Window");

    // Folder file selection
    QString title = "Import Algorithm data";
    QString directory = "C://";
    QString selectDir = QFileDialog::getExistingDirectory(w,title,directory,QFileDialog::DontResolveSymlinks | QFileDialog::DontUseNativeDialog);

    if (selectDir.isEmpty()) // No folder selected
    {
        Tools::debugMessage("Algorithm opening cancel");
        w->ui->statusBar->showMessage("Algorithm loading cancel !",0);
        return false;
    }

    //==================================================================================================================
    //== DATA LOADING ==
    //==================================================================================================================
    w->ui->statusBar->showMessage("Loading...");

    QStringList listFilter; // We fill a QStringList with each filter wanted, here "*.txt"
    listFilter << "*.txt";

    // We declare an QDirIterator in which we explain we want cover a directory and his sub-directory.
    // We specify the filter which allows to only get the wanted file type ("*.txt")
    QDirIterator dirIterator(selectDir, listFilter ,QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);

    while(dirIterator.hasNext()) // While we have others sub-folders...
    {
        QString temp = dirIterator.next(); // We store the directory fileName
        if (temp.contains(w->getVideoController()->getLoadedVideo()->getFileName()))
        {
            objectList_ << temp;
        }
        else if (temp.contains("FrameHyp"))
        {
            frameHypList_ << temp;
        }
        else if (temp.contains("Graphe"))
        {
            graphList_ << temp;
        }
        else
        {
            w->ui->statusBar->showMessage("The video doesn't match. Can't load the files.",0);
            return false;
        }
    }

    Tools::debugMessage("Size objectList",objectList_.size());
    Tools::debugMessage("Size frameHypList",frameHypList_.size());
    Tools::debugMessage("Size grapheList",graphList_.size());


    //==================================================================================================================
    //== ELEMENTS CREATION ==
    //==================================================================================================================

    //== OBJECTS ==
    createObject(objectList_.at(0));
    Tools::debugMessage("OBJECTS : LOADING FILES COMPLETE");

    //== FRAMEHYP ==
    foreach (QString str, frameHypList_)
    {
        createFrameHyp(str);
    }
    Tools::debugMessage("FRAMES HYP : LOADING FILES COMPLETE");

    //== GRAPH ==
    foreach (QString str, graphList_)
    {
        createGraph(str);
    }
    Tools::debugMessage("GRAPH : LOADING FILES COMPLETE");

    w->ui->statusBar->showMessage("Loading complete !",0);
    return true;
}

/**
 * File reading to create loaded video object
 * @brief C_Algorithm::createObject
 * @param str the file containing the objects data
 * @return true if the creation process is achieved, else false
 */
bool C_Algorithm::createObject(QString str)
{
    //==================================================================================================================
    //== OPENING THE FILE (ReadOnly) ==
    //==================================================================================================================
    MainWindow *w = (MainWindow *)parent();
    QFile file(str);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&file);

    if(file.isOpen())
    {
        int index = -1; // frame index for which we create the objects
        QString line;
        while(!stream.atEnd()) // while we're not at the end of file
        {
            line = stream.readLine();

            if(line.contains("Frame"))
            {
                // We get the frame index
                QStringList list;
                list = line.split('\t');
                index = list.at(1).toInt();
                // Tools::debugMessage("Frame Index ", index);
            }
            else
            {

                // We create an OBJECT with the separated word get on the current line
                QStringList list;
                list = line.split('\t');

                Object objet = Object(list.at(0).toInt(), cv::Point2f(list.at(1).toInt(),list.at(2).toInt()), cv::Point2f(list.at(3).toInt(),list.at(4).toInt()));

//                Tools::debugMessage("OBJECT ID ", objet.getIdObjet());
//                Tools::debugMessage("getLeftTopPoint().x", objet.getLeftTopPoint().x);
//                Tools::debugMessage("getLeftTopPoint().y", objet.getLeftTopPoint().y);
//                Tools::debugMessage("getRightBottomPoint().x", objet.getRightBottomPoint().x);
//                Tools::debugMessage("getRightBott omPoint().y", objet.getRightBottomPoint().y);

                //==================================================================================================================
                //== OBJECT ADDING ==
                //==================================================================================================================
                w->getVideoController()->getLoadedVideo()->getFramesList()[index].addObject(objet);
            }
        }
        file.close();
        return true;
    }
    else
    {
        Tools::debugMessage("unable to open the file : " + str);
        return false;
    }
}

/**
 * File reading to create Graph data
 * @brief C_Algorithm::createGraph
 * @param str the file containing the objects data
 * @return true if the creation process is achieved, else false
 */
bool C_Algorithm::createGraph(QString str)
{
    MainWindow *w = (MainWindow *)parent();
    QFile file(str);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&file);

    if(file.isOpen())
    {
        // 1st line : number of nodes in the graph
        QString line = stream.readLine();

        //==================================================================================================================
        //== GRAPH CREATION ==
        //==================================================================================================================
        int nbNodes = line.toInt();
        Graph *graphe = new Graph(nbNodes);

        //==================================================================================================================
        //== NODES CREATION for the Graph ==
        //==================================================================================================================
        for (int i=0;i<nbNodes;i++)
        {
            QString nodeLine = stream.readLine(); // Read line
            QStringList listNode = nodeLine.split('\t');

//            Tools::debugMessage("ID NODE", listNode.at(0).toUInt());
//            Tools::debugMessage("LABEL OBJET", listNode.at(1).toUInt());
//            Tools::debugMessage("POSITION X", listNode.at(2).toInt());
//            Tools::debugMessage("POSITION Y", listNode.at(3).toInt());
//            Tools::debugMessage("DIM HEIGHT", listNode.at(4).toInt());
//            Tools::debugMessage("DIM WIDTH", listNode.at(5).toInt());

            // If the attribute is Visible or not
            bool isVisible = false;
            if (listNode.at(6).toInt()==1)
            {
                isVisible = true;
            }
//            Tools::debugMessage("VISIBLE", isVisible);

            Node nodeSource = Node(listNode.at(0).toUInt(),listNode.at(1).toUInt(),cv::Point2f(listNode.at(2).toInt(),listNode.at(3).toInt()),listNode.at(4).toInt(), listNode.at(5).toInt(), isVisible);
            graphe->addNode(nodeSource); // we append the node to the graph's nodelist


            //==================================================================================================================
            //== EDGES CREATION==
            //==================================================================================================================

            // Number of edges leave the current node
            line = stream.readLine();
            int nbEdges = line.toInt();

            for (int j=0;j<nbEdges;j++)
            {
                QString edgeLine = stream.readLine();
                QStringList listEdge = edgeLine.split('\t');

//                Tools::debugMessage("ID SOURCE NODE", nodeSource.getIdNode());
//                Tools::debugMessage("ID DESTINATION NOEUD", listEdge.at(0).toUInt());
//                Tools::debugMessage("EDGE WEIGHT", listEdge.at(1).toDouble());

                Edge edge = Edge(nodeSource.getIdNode(), listEdge.at(0).toUInt(), listEdge.at(1).toDouble());
                graphe->addEdge(edge); // we append the edge to the graph's edgelist
            }
        }

        // We add the graph to the concern frame
        // We catch the filename to know the frame number and the graph number
        QFileInfo fileInfo(str);
        QString filenameWithoutExt = fileInfo.baseName();

        QString temp = filenameWithoutExt.remove("Graphe");
        QStringList tempList = temp.split('_');
        //Tools::debugMessage("tempList[0]",tempList.at(0).toInt());
        //Tools::debugMessage("tempList[1]",tempList.at(1).toUInt());

        graphe->setIdGraph(tempList.at(1).toUInt());
        graphe->setWeightParticle(map.value(fileInfo.fileName()));
        //Tools::debugMessage("map value",graphe.getWeightParticle());
        w->getVideoController()->getLoadedVideo()->getFramesList()[tempList.at(0).toInt()].addParticleToFrame(graphe);


        //Tools::debugMessage("Number of particles in the frame",w->getVideoController()->getVideoChargee()->getFrames()[tempList.at(0).toUInt()].getListParticules().size());
        return true;
    }
    else
    {
        Tools::debugMessage("Unable to open the file !" + str);
        return false;
    }
}

/**
 * Read the FrameHyp files from the algorithm
 * @brief C_Algorithm::createFrameHyp
 * @param str
 * @return true si le création se fait correctement, false sinon
 */
bool C_Algorithm::createFrameHyp(QString str)
{
    QFile file(str);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&file);

    if(file.isOpen())
    {
        QString line;
        while(!stream.atEnd())
        {
            line = stream.readLine();
            QStringList tempList = line.split('\t');
            //Tools::debugMessage("tempList[0]",tempList.at(0));
            //Tools::debugMessage("tempList[1]",tempList.at(1).toDouble());
            map[tempList.at(0)]=tempList.at(1).toDouble();
        }
        return true;
    }
    else
    {
        Tools::debugMessage("Impossible d'ouvrir le fichier !" + str);
        return false;
    }
}


/**********************************************************************/
/*                              DISPLAY                               */
/**********************************************************************/

/**
 * Display the object list in the debug console
 * @brief C_Algorithm::displayObjectList
 */
void C_Algorithm::displayObjectList()
{
    Tools::debugMessage("objectList");
    for (int i = 0; i < objectList_.size(); ++i)
    {
        Tools::debugMessage("["+objectList_[i]+"] ");
    }
}

/**
 * Display the FrameHyp list in the debug console
 * @brief C_Algorithm::displayFrameHypList
 */
void C_Algorithm::displayFrameHypList()
{
    Tools::debugMessage("frameHypList");
    for (int i = 0; i < frameHypList_.size(); ++i)
    {
        Tools::debugMessage("["+frameHypList_[i]+"] ");
    }
}


/**
 * Display the graph list in the debug console
 * @brief C_Algorithm::displayGrapheList
 */
void C_Algorithm::displayGrapheList()
{
    Tools::debugMessage("grapheList");
    for (int i = 0; i < objectList_.size(); ++i)
    {
        Tools::debugMessage("["+graphList_[i]+"] ");
    }
}
