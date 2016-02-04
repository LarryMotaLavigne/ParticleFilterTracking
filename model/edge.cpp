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

