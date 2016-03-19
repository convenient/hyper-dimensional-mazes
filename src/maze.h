#ifndef MAZES_FOR_PROGRAMMERS_MAZE_H
#define MAZES_FOR_PROGRAMMERS_MAZE_H

#include "node.h"

class Maze {
private:
    std::unordered_map<std::string, Node *> map;

public:
    Node* createNode(Point p) {
        if (this->nodeExistsAtPoint(p)) {
            throw std::logic_error("Tried to create a node where already exists");
        }

        Node* n = new Node(p);

        this->map.insert({p.getAsString(), n});
        return n;
    }


    bool nodeExistsAtPoint(Point p) {
        std::string identifier = p.getAsString();
        if (this->map.count(identifier)) {
            return true;
        }
        return false;
    }

    void connectNodes(Node *a, Node *b) {
        if (!this->nodeExistsAtPoint(a->getPoint()) || !this->nodeExistsAtPoint(b->getPoint())) {
            throw std::logic_error("Tried to connect two nodes which do not exist");
        }

        a->link(b);
    }

    std::unordered_map<std::string, Node *> getMap() {
        return this->map;
    }
};

#endif //MAZES_FOR_PROGRAMMERS_MAZE_H
