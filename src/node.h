#ifndef MAZES_FOR_PROGRAMMERS_NODE_H
#define MAZES_FOR_PROGRAMMERS_NODE_H

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

        if (ptr == this) {
            return;
        } else if (!((ptr == NULL) || (ptr == nullptr))) {
            return;
        }

        node->setLeftPtr(this);
    }

    public: void setLeftPtr(Node *node)
    {
        this->x_minus = node;
        Node* ptr = node->getRightPtr();

        if (ptr == this) {
            return;
        } else if (!((ptr == NULL) || (ptr == nullptr))) {
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
