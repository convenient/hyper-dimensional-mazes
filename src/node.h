#ifndef MAZES_FOR_PROGRAMMERS_NODE_H
#define MAZES_FOR_PROGRAMMERS_NODE_H

#include <stdexcept>
#include <unordered_map>
#include "axis.h"

class Node {

private:
    const char x = 'x';
    std::unordered_map<char, Axis> dimensions;

public:
    Node()
    {
        Axis x_axis;
        this->dimensions.insert({this->x, x_axis});
    }

    void setRightPtr(Node *node) {
        this->setPtr(this->x, Axis::positive, node);
    }

    Node *getRightPtr() {
        return this->getPtr(this->x, Axis::positive);
    }

    void setLeftPtr(Node *node) {
        this->setPtr(this->x, Axis::negative, node);
    }

    Node *getLeftPtr() {
        return this->getPtr(this->x, Axis::negative);
    }

    Axis* getAxis(char axis)
    {
        if (this->dimensions.count(axis)) {
            return &this->dimensions.at(axis);
        } else {
            throw std::logic_error("Unexpected axis requested");
        }
    }

private:

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
