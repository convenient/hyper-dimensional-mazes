#ifndef MAZES_FOR_PROGRAMMERS_NODE_H
#define MAZES_FOR_PROGRAMMERS_NODE_H

#include <stdexcept>

class Node {

    Node* x_plus = nullptr;
    Node* x_minus = nullptr;
    Node* y_plus = nullptr;
    Node* y_minus = nullptr;

    public: Node()
    {
    }

    public: void setRightPtr(Node *node)
    {
        this->x_plus = node;

        Node* ptr = node->getLeftPtr();

        if (this->shouldUpdatePtr(ptr)) {
            node->setLeftPtr(this);
        }
    }

    public: void setLeftPtr(Node *node)
    {
        this->x_minus = node;

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
