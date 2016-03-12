#ifndef MAZES_FOR_PROGRAMMERS_NODE_H
#define MAZES_FOR_PROGRAMMERS_NODE_H

#include <stdexcept>
#include <unordered_map>
#include <string>

class Node {

private:
    const std::string positive = "positive";
    const std::string negative = "negative";

    std::unordered_map<std::string, Node*> x_axis;

public:
    void setRightPtr(Node *node) {
        this->setPtr(node, this->positive);
    }

    Node *getRightPtr() {
        return this->getPtr(this->positive);
    }

    void setLeftPtr(Node *node) {
        this->setPtr(node, this->negative);
    }

    Node *getLeftPtr() {
        return this->getPtr(this->negative);
    }

private:

    void setPtr(Node *node, std::string direction){
        Node *currentPtr = this->getPtr(direction);
        if (currentPtr == node) {
            return;
        }

        this->safeInsert(direction, node);

        std::string oppositeDirection = this->getOppositeDirection(direction);

        /**
         * Break the link with the current sister node.
         */
        if (currentPtr != nullptr) {
            currentPtr->setPtr(nullptr, oppositeDirection);
        }

        if (node == nullptr) {
            return;
        }

        /**
         * Link the new sister node
         */
        Node *ptr = node->getPtr(oppositeDirection);

        if (this->shouldUpdatePtr(ptr)) {
            node->setPtr(this, oppositeDirection);
        }
    }

    Node *getPtr(std::string direction) {
        if (this->x_axis.count(direction)) {
            return this->x_axis.at(direction);
        } else {
            return nullptr;
        }
    }

    void safeInsert(std::string direction, Node *node)
    {
        if (this->x_axis.count(direction)) {
            this->x_axis.erase(direction);
        }
        this->x_axis.insert({direction, node});
    }

    std::string getOppositeDirection(std::string direction) {
        if (direction == this->positive) {
            return this->negative;
        } else if (direction == this->negative) {
            return this->positive;
        } else {
            throw std::logic_error("Unexpected axis direction given");
        }
    }

    bool shouldUpdatePtr(Node *ptr) {
        if (ptr == this) {
            //Already paired
            return false;
        } else if (ptr == nullptr) {
            //Ptr unassigned, free to pair
            //Don't think this condition should actually be hit.
            return true;
        } else {
            throw std::logic_error("Should pair with something else");
        }
    }
};


#endif //MAZES_FOR_PROGRAMMERS_NODE_H
