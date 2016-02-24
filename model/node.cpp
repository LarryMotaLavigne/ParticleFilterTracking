#include "model/node.h"

/**
 * Constructor
 * @brief Node::Node
 * @param idNode
 * @param labelObject
 * @param positionNode
 * @param dimHeightNode
 * @param dimWidthNode
 * @param isVisibleNode
 */
Node::Node(unsigned int idNode, unsigned int objectLabel, cv::Point2f nodePosition, unsigned int nodeWidth, unsigned int nodeHeight, bool isVisibleNode)
{
    this->idNode_ = idNode;
    this->objectLabel_ = objectLabel;
    this->nodePosition_ = nodePosition;
    this->nodeWidth_ = nodeWidth;
    this->nodeHeight_ = nodeHeight;
    this->isVisibleNode_ = isVisibleNode;
}

/**
 * Destructor
 * @brief Node::~Node
 */
Node::~Node()
{

}


/**
 * Copy constructor
 * @brief Node::Node
 * @param other the node to copy
 */
Node::Node(const Node& other)
{
    this->idNode_ = other.idNode_;
    this->objectLabel_ = other.objectLabel_;
    this->nodePosition_.x = other.nodePosition_.x;
    this->nodePosition_.y = other.nodePosition_.y;
    this->nodeHeight_ = other.nodeHeight_;
    this->nodeWidth_ = other.nodeWidth_;
    this->isVisibleNode_ = other.isVisibleNode_;
}




/**********************************************************************/
/*                               GETTER                               */
/**********************************************************************/

/**
 * Get the node id
 * @brief Node::getIdNode
 * @return idNode_ the node id
 */
unsigned int Node::getIdNode()
{
    return idNode_;
}

/**
 * Get the position of a specific node
 * @brief Node::getPositionNode
 * @return nodePosition_ the position of the node
 */
cv::Point2f Node::getPositionNode()
{
    return nodePosition_;
}

/**
 * Get the node height
 * @brief Node::getNodeHeight
 * @return nodeHeight_ the height of the node
 */
unsigned int Node::getNodeHeight()
{
    return nodeHeight_;
}

/**
 * Get the node width
 * @brief Node::getNodeWidth
 * @return nodeWidth_ the width of the node
 */
unsigned int Node::getNodeWidth()
{
    return nodeWidth_;
}

/**
 * Get the left top point of the rectangle
 * @brief Node::getLeftTopPoint
 * @return point the point of the left top corner
 */
cv::Point Node::getLeftTopPoint()
{
    int x = nodePosition_.x - nodeWidth_/2;
    int y = nodePosition_.y - nodeHeight_/2;
    return cv::Point(x,y);
}


/**
 * Get the right bottom point of the rectangle
 * @brief Node::getRightBottomPoint
 * @return point the point of the right bottom corner
 */
cv::Point Node::getRightBottomPoint()
{
    int x = nodePosition_.x + nodeWidth_/2;
    int y = nodePosition_.y + nodeHeight_/2;
    return cv::Point(x,y);
}
