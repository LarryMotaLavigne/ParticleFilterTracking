#include "model/edge.h"

/**
 * Default Constructor
 * @brief Edge::Edge
 */
Edge::Edge()
{

}

/**
 * Constructor
 * @brief Edge::Edge
 * @param sourceNode the source node
 * @param destinationNode the destination node
 * @param edgeWeight the edge weight
 */
Edge::Edge(unsigned int sourceNode, unsigned int destinationNode, double edgeWeight)
{
    this->sourceNode_ = sourceNode;
    this->destinationNode_ = destinationNode;
    this->edgeWeight_ = edgeWeight;
}

/**
 * Copy Constructor
 * @brief Edge::Edge
 * @param other the edge to copy
 */
Edge::Edge(const Edge& other)
{
     this->sourceNode_ = other.sourceNode_;
     this->destinationNode_ = other.destinationNode_;
     this->edgeWeight_ = other.edgeWeight_;
}

/**
 * Destructor
 * @brief Edge::~Edge
 */
Edge::~Edge()
{

}

/**********************************************************************/
/*                               GETTER                               */
/**********************************************************************/

/**
 * Get the id of the source node
 * @brief Edge::getSourceNode
 * @return the id of the source node
 */
unsigned int Edge::getSourceNode()
{
    return this->sourceNode_;
}


/**
 * Get the id of the destination node
 * @brief Edge::getDestinationNode
 * @return the id of the destination node
 */
unsigned int Edge::getDestinationNode()
{
    return this->destinationNode_;
}

