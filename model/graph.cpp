#include "model/graph.h"

/**
 * Default constructor
 * @brief Graph::Graph
 */
Graph::Graph()
{

}

/**
 * Constructor
 * @brief Graph::Graph
 * @param nodesCount the number of nodes
 */
Graph::Graph(unsigned int nodesCount)
{
    this->nodesCount_ = nodesCount;
}

/**
 * Destructor
 * @brief Graph::~Graph
 */
Graph::~Graph()
{

}

/**
 * Copy constructor
 * @brief Graph::Graph
 * @param other the graph to copy
 */
Graph::Graph(const Graph& other)
{
    this->particleId_ = other.particleId_;
    this->nodesCount_ = other.nodesCount_;

    this->nodesList_ = other.nodesList_;
    this->edgesList_ = other.edgesList_;
}


/**********************************************************************/
/*                               GETTER                               */
/**********************************************************************/

/**
 * Get the nodes list
 * @brief Graph::getNodesList
 * @return nodesList_ the nodes list
 */
QList<Node>& Graph::getNodesList()
{
    return nodesList_;
}

/**
 * Get the edges list
 * @brief Graph::getEdgesList
 * @return edgesList_ the edges list
 */
QList<Edge>& Graph::getEdgesList()
{
    return edgesList_;
}

/**
 * Get the number of nodes in the graph
 * @brief Graph::getNodesCount
 * @return nodesCount_ the number of nodes
 */
unsigned int Graph::getNodesCount()
{
    return nodesCount_;
}

/**********************************************************************/
/*                               SETTER                               */
/**********************************************************************/

/**
 * Set the graph id
 * @brief Graph::setIdGraph
 * @param id the new id
 */
void Graph::setIdGraph(unsigned int id)
{
    particleId_ = id;
}


/**********************************************************************/
/*                          ADDING FUNCTIONS                          */
/**********************************************************************/

/**
 * Add a new node to the graph
 * @brief Graph::addNode
 * @param node the new node to add
 */
void Graph::addNode(Node node)
{
    nodesList_.append(node);
}

/**
 * Add a new edge to the graph
 * @brief Graph::addEdge
 * @param edge the new edge to add
 */
void Graph::addEdge(Edge edge)
{
    edgesList_.append(edge);
}


/**********************************************************************/
/*                          DRAWING FUNCTION                          */
/**********************************************************************/

/**
 * Draw all the particle related to the graph
 * @brief Graph::drawParticle
 * @param img the image
 */
void Graph::drawParticle(cv::Mat &img)
{
    // DRAW EACH NODE
//    std::cout<<"nodeList.size() : "<<nodesList_.size()<<std::endl;
    for (int i = 0; i < nodesList_.size(); ++i)
    {
//        std::cout<<"Node "<<i<<" , Position : ("<<nodesList_[i].getPositionNode().x<<","<<nodesList_[i].getPositionNode().y<<")"<<std::endl;
        cv::circle(img,nodesList_[i].getPositionNode(),3,cv::Scalar(255,0,0),-1);
    }

    // DRAW EACH EDGE
    cv::Point2f start(0,0);
    cv::Point2f end(0,0);
    for(int i = 0; i < edgesList_.size() ; ++i)
    {
        for(int j = 0 ; j < nodesList_.size() ; ++j)
        {

            if(nodesList_[j].getIdNode() == edgesList_[i].getSourceNode() || nodesList_[j].getIdNode() == edgesList_[i].getDestinationNode())
            {
                if(start.x == 0 && start.y == 0)
                {
                    start = nodesList_[j].getPositionNode();
                }
                else
                {
                    end = nodesList_[j].getPositionNode();
                }
            }
        }
        cv::line(img, start, end, cv::Scalar(255,0,0));
    }

}

