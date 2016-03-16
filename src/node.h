#ifndef MAZES_FOR_PROGRAMMERS_NODE_H
#define MAZES_FOR_PROGRAMMERS_NODE_H

#include <stdexcept>
#include "dimensions.h"

class Node {

private:
    Dimensions dimensions;

public:
    Node(Dimensions dimensions)
    {
        this->dimensions = dimensions;
    }

    Axis* getAxis(char axis)
    {
        return this->dimensions.getAxisPtr(axis);
    }

    void setPtr(char axis, int direction, Node *node){
        Axis* axisObject = this->getAxis(axis);
        Node *currentPtr = this->getPtr(axis, direction);
        if (currentPtr == node) {
            return;
        }

        axisObject->setPtr(direction, node);

        int oppositeDirection = axisObject->getOppositeDirection(direction);

        /**
         * Break the link with the current sister node.
         */
        if (currentPtr != nullptr) {
            currentPtr->setPtr(axis, oppositeDirection, nullptr);
        }

        if (node == nullptr) {
            return;
        }

        /**
         * Link the new sister node
         */
        Node *ptr = node->getPtr(axis, oppositeDirection);

        if (this->shouldUpdatePtr(ptr)) {
            node->setPtr(axis, oppositeDirection, this);
        }
    }

    Node *getPtr(char axis, int direction) {
        Axis* axisObject = this->getAxis(axis);
        Node* node = (Node*) axisObject->getPtr(direction);
        return node;
    }

private:
    bool shouldUpdatePtr(Node *ptr) {
        if (ptr == this) {
            //Already paired
            return false;
        } else if (ptr == nullptr) {
            //Ptr unassigned, free to pair
            return true;
        } else {
            throw std::logic_error("Should pair with something else");
        }
    }
};


#endif //MAZES_FOR_PROGRAMMERS_NODE_H
