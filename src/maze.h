#ifndef MAZES_FOR_PROGRAMMERS_MAZE_H
#define MAZES_FOR_PROGRAMMERS_MAZE_H

#include "node.h"
#include <random>

class Maze {
private:
    std::unordered_map<std::string, Node *> map;

public:

    Node* getRandomNode() {

        if (this->map.size() < 1) {
            throw std::logic_error("Tried to get random node when none in maze");
        }

        //http://stackoverflow.com/a/12658029/4354325
        std::mt19937 rng(3141);
        std::uniform_int_distribution<int> gen(0, (int)this->map.size() -1);
        int r = gen(rng);

        //http://stackoverflow.com/a/27024374/4354325
        auto random_it = std::next(std::begin(this->map), r);

        std::string key = random_it->first;
        return this->map.at(key);
    }

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

    void connectNodes(Point a, Point b) {
        if (this->nodeExistsAtPoint(a) && this->nodeExistsAtPoint(b)) {
            Node *nodeA = this->map.at(a.getAsString());
            Node *nodeB = this->map.at(b.getAsString());

            return this->connectNodes(nodeA, nodeB);
        }
        throw std::logic_error("Tried to connect two nodes which do not exist");
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
