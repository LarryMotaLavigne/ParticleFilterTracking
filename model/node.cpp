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
Node::Node(unsigned int idNode, unsigned int objectLabel, cv::Point2f nodePosition, unsigned int nodeHeight, unsigned int nodeWidth, bool isVisibleNode)
{
    this->idNode_ = idNode;
    this->objectLabel_ = objectLabel;
    this->nodePosition_ = nodePosition;
    this->nodeHeight_ = nodeHeight;
    this->nodeWidth_ = nodeWidth;
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
