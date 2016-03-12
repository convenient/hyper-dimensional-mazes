#ifndef MAZES_FOR_PROGRAMMERS_NODE_H
#define MAZES_FOR_PROGRAMMERS_NODE_H

#include <stdexcept>
#include <unordered_map>
#include <string>

class Node {

public: Node()
    {
        std::unordered_map<std::string, Node*> x_axis;
        std::unordered_map<std::string, Node*> y_axis;
        //std::unordered_map<std::string, Node*> z_axis;

        this->dimensions.insert({this->x, x_axis});
        this->dimensions.insert({this->y, y_axis});
        //this->dimensions.insert({this->z, x_axis});
    }

private:
    const std::string positive = "positive";
    const std::string negative = "negative";
    const char x = 'x';
    const char y = 'y';
    const char z = 'z';

    std::unordered_map<std::string, Node*> x_axis;
    std::unordered_map<char, std::unordered_map<std::string, Node*>> dimensions;

public:
    void setRightPtr(Node *node) {
        std::unordered_map<std::string, Node*>* x_axis = this->getAxis(this->x);

        this->setPtr(x_axis, node, this->positive);
    }

    Node *getRightPtr() {
        std::unordered_map<std::string, Node*>* x_axis = this->getAxis(this->x);

        return this->getPtr(x_axis, this->positive);
    }

    void setLeftPtr(Node *node) {
        std::unordered_map<std::string, Node*>* x_axis = this->getAxis(this->x);

        this->setPtr(x_axis, node, this->negative);
    }

    Node *getLeftPtr() {

        std::unordered_map<std::string, Node*>* x_axis = this->getAxis(this->x);

        return this->getPtr(x_axis, this->negative);
    }

private:

    std::unordered_map<std::string, Node*>* getAxis(char axis)
    {
        if (this->dimensions.count(axis)) {
            return &this->dimensions.at(axis);
        } else {
            return nullptr;
        }
    }

    void setPtr(std::unordered_map<std::string, Node*>* axis, Node *node, std::string direction){
        Node *currentPtr = this->getPtr(axis, direction);
        if (currentPtr == node) {
            return;
        }

        this->safeInsert(direction, node);

        std::string oppositeDirection = this->getOppositeDirection(direction);

        /**
         * Break the link with the current sister node.
         */
        if (currentPtr != nullptr) {
            currentPtr->setPtr(axis, nullptr, oppositeDirection);
        }

        if (node == nullptr) {
            return;
        }

        /**
         * Link the new sister node
         */
        Node *ptr = node->getPtr(axis, oppositeDirection);

        if (this->shouldUpdatePtr(ptr)) {
            node->setPtr(axis, this, oppositeDirection);
        }
    }

    Node *getPtr(std::unordered_map<std::string, Node*>* axis, std::string direction) {
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
