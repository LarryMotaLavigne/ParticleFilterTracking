#ifndef EDGE_H
#define EDGE_H

#include "tools.h"

class Edge
{
private:
    unsigned int sourceNode_; // Source Node id
    unsigned int destinationNode_; // Destination Node id
    double edgeWeight_; // Edge Weight
public:
    Edge();
    Edge(unsigned int sourceNode, unsigned int destinationNode, double edgeWeight);
    Edge(const Edge& other);
    ~Edge();

    /********** GETTER *********/
    unsigned int getSourceNode();
    unsigned int getDestinationNode();
};

#endif // EDGE_H
