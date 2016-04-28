#ifndef MAZES_FOR_PROGRAMMERS_NODE_H
#define MAZES_FOR_PROGRAMMERS_NODE_H

#include <stdexcept>
#include "point.h"
#include <unordered_map>

class Node {
private:
    std::unordered_map<Node*, Point> linkedNodes;
    Point point;

public:

    Node(Point p) {
        this->point = p;
    }

    void setPoint(Point p) {
        this->point = p;
    }

    Point getPoint() {
        return this->point;
    }

    void clearLinkedNodes() {
        this->linkedNodes.clear();
    }

    void link(Node *node) {
        if (!this->isLinked(node)) {
            this->linkedNodes.insert({node, node->getPoint()});
            node->link(this);
        }
    }

    void unlink(Node *node) {
        if (this->isLinked(node)) {
            this->linkedNodes.erase({node});
            return node->unlink(this);
        }
    }

    bool isLinked(Point p) {
        for (auto i : this->linkedNodes) {
            Point p1 = i.second;
            if (p.getAsString() == p1.getAsString()) {
                return true;
            }
        }

        return false;
    }

    bool isLinked(Node *node) {
        if (this->linkedNodes.count(node)) {
            return true;
        }
        return false;
    }

    std::vector<Node *> getLinkedNodes() {
        std::vector<Node *> linked;

        for (auto i : this->linkedNodes) {
            Node *n = i.first;
            linked.push_back(n);
        }

        return linked;
    }
};


#endif //MAZES_FOR_PROGRAMMERS_NODE_H
