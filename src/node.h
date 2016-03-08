#ifndef MAZES_FOR_PROGRAMMERS_NODE_H
#define MAZES_FOR_PROGRAMMERS_NODE_H

class Node {

    Node* x_plus;
    Node* x_minus;
    Node* y_plus;
    Node* y_minus;

    public: Node()
    {
    }

    public: void setRightPtr(Node *node)
    {
        this->x_plus = node;

        Node* leftPtr = node->getLeftPtr();

        if (leftPtr == NULL) {
            return;
        } else if (leftPtr == this) {
            return;
        }

        node->setLeftPtr(this);
    }

    public: void setLeftPtr(Node *node)
    {
        this->x_minus = node;
        Node* rightPtr = node->getRightPtr();

        if (rightPtr == NULL) {
            return;
        } else if (rightPtr == this) {
            return;
        }

        node->setRightPtr(this);
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
