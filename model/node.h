#ifndef NODE_H
#define NODE_H

#include <opencv/cv.h>

class Node
{
private:
    unsigned int idNode_; // node id
    unsigned int objectLabel_; // id of the object represented by the node
    cv::Point2f nodePosition_; // Node position (central point)
    unsigned int nodeHeight_; // Node height
    unsigned int nodeWidth_; // Node width

    bool isVisibleNode_; // Node visibility

public:
    Node();
    Node(unsigned int idNode, unsigned int objectLabel, cv::Point2f nodePosition, unsigned int nodeHeight, unsigned int nodeWidth, bool isVisibleNode);
    Node(const Node& other);
    ~Node();

    /***** GETTER *****/
    unsigned int getIdNode();
    cv::Point2f getPositionNode();
};

#endif // NODE_H
