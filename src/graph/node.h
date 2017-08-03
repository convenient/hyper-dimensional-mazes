#ifndef MAZES_FOR_PROGRAMMERS_NODE_H
#define MAZES_FOR_PROGRAMMERS_NODE_H

#include <stdexcept>
#include "point.h"
#include <unordered_map>

class Node {
private:
    std::unordered_map<Node*, Point> linkedNodes;
    std::vector<Node *> linkedNodesVector;
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
        this->linkedNodesVector.clear();
    }

    void link(Node *node) {
        if (node == this) {
            throw new std::logic_error("a node cannot link to itself!");
        }
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

        if (this->linkedNodesVector.size()<=0) {
            this->linkedNodesVector = this->getLinkedNodesUncached();
        }

        return this->linkedNodesVector;
    }

    std::vector<Node *> getLinkedNodesUncached() {
        std::vector<Node *> linkedNodes;
        for (auto i : this->linkedNodes) {
            Node *n = i.first;
            linkedNodes.push_back(n);
        }
        return linkedNodes;
    }
};


#endif //MAZES_FOR_PROGRAMMERS_NODE_H
