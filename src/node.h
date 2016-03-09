#ifndef MAZES_FOR_PROGRAMMERS_NODE_H
#define MAZES_FOR_PROGRAMMERS_NODE_H

#include <stdexcept>

class Node {

    Node* x_plus = nullptr;
    Node* x_minus = nullptr;

    public: void setRightPtr(Node *node)
    {
        Node*currentPtr = this->x_plus;
        if (currentPtr == node) {
            return;
        }
        this->x_plus = node;

        if (currentPtr != nullptr) {
            currentPtr->setLeftPtr(nullptr);
        }

        if (node == nullptr) {
            return;
        }

        Node* ptr = node->getLeftPtr();

        if (this->shouldUpdatePtr(ptr)) {
            node->setLeftPtr(this);
        }
    }

    public: void setLeftPtr(Node *node)
    {
        Node*currentPtr = this->x_minus;
        if (currentPtr == node) {
            return;
        }
        this->x_minus = node;

        if (currentPtr != nullptr) {
            currentPtr->setRightPtr(nullptr);
        }


        if (node == nullptr) {
            return;
        }

        Node* ptr = node->getRightPtr();

        if (this->shouldUpdatePtr(ptr)) {
            node->setRightPtr(this);
        }
    }

    private: bool shouldUpdatePtr(Node*ptr)
    {
        if (ptr == this) {
            //Already paired
            return false;
        } else if (ptr == nullptr) {
            //Ptr unassigned, free to pair
            //Don't think this condition should actually be hit.
            return true;
        } else {
            throw std::logic_error( "Should pair with something else" );
        }
    }

    public: Node*getRightPtr()
    {
        return this->x_plus;
    }

    public: Node*getLeftPtr()
    {
        return this->x_minus;
    }
};


#endif //MAZES_FOR_PROGRAMMERS_NODE_H
