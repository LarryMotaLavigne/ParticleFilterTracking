#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>

#include "model/node.h"
#include "model/edge.h"
#include "model/particle.h"


class Graph : public Particle
{

private:
    int nodesCount_; // number of nodes in the graph

    QList<Node> nodesList_; // nodes list
    QList<Edge> edgesList_; // edges list

public:
    Graph();
    Graph(unsigned int nodesCount);
    Graph(const Graph& other);
    ~Graph();


    /***** GETTER *****/
    QList<Node> &getNodesList();
    QList<Edge> &getEdgesList();
    unsigned int getNodesCount();

    /***** SETTER *****/
    void setIdGraph(unsigned int id);

    /***** ADDING FUNCTIONS *****/
    void addNode(Node node);
    void addEdge(Edge edge);

    /***** DRAWING FUNCTION *****/
    void drawParticle(cv::Mat& img);
};

#endif // GRAPH_H
