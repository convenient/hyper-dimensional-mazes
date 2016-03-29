#ifndef MAZES_FOR_PROGRAMMERS_MAZE_H
#define MAZES_FOR_PROGRAMMERS_MAZE_H

#include "node.h"
#include <random>
#include <string>
#include <chrono>

class Maze {
private:
    std::unordered_map<std::string, Node *> map;
    std::unordered_map<std::string, Node *> visited_map;
    std::unordered_map<std::string, Node *> unvisited_map;
    std::mt19937 rng;
    bool rngSeeded = false;

    Node* getRandomNode(std::unordered_map<std::string, Node *> map) {

        if (map.size() < 1) {
            throw std::logic_error("Tried to get random node when none in maze");
        }

        int r = this->getRandomNumber(0, (int)map.size() -1);

        //http://stackoverflow.com/a/27024374/4354325
        auto random_it = std::next(std::begin(map), r);

        std::string key = random_it->first;
        return map.at(key);
    }

public:

    int getRandomNumber(int min, int max) {
        if (!this->rngSeeded) {
            typedef std::chrono::high_resolution_clock myclock;
            myclock::time_point beginning = myclock::now();

            myclock::duration d = myclock::now() - beginning;
            unsigned seed = d.count();

            this->rng.seed(seed);
        }

        std::uniform_int_distribution<int> gen(min, max);
        int r = gen(rng);

        return r;
    }

    void markNodeAsVisited(Node *node) {
        Point p = node->getPoint();
        if (this->nodeExistsAtPoint(p)) {
            std::string pointId = p.getAsString();
            if (this->unvisited_map.count(pointId)) {
                this->unvisited_map.erase(pointId);
                this->visited_map.insert({pointId, node});
                return;
            }
        }
        throw std::logic_error("Tried to mark a node as visited when it does not exist");
    }

    Node* getRandomUnvisitedNode() {
        return this->getRandomNode(this->unvisited_map);
    };

    Node* getRandomNode() {
        return this->getRandomNode(this->map);
    }

    std::vector<std::string> getAllAxis(){

        std::map<std::string, std::string> allDefinedAxis;

        for (auto nodeItr : this->getMap()) {
            Node *node = nodeItr.second;
            Point p = node->getPoint();

            for (auto axisItr : p.getDefinedAxis()) {
                std::string axisIdentifier = axisItr.first;
                if (!allDefinedAxis.count(axisIdentifier)) {
                    allDefinedAxis.insert({axisIdentifier, axisIdentifier});
                }
            }
        }

        std::vector<std::string> axis;

        for (auto i: allDefinedAxis) {
            std::string axisIdentifier = i.first;
            axis.push_back(axisIdentifier);
        }

        return axis;
    }

    Node* createNode(Point p) {
        if (this->nodeExistsAtPoint(p)) {
            throw std::logic_error("Tried to create a node where already exists");
        }

        Node* n = new Node(p);

        this->map.insert({p.getAsString(), n});
        this->unvisited_map.insert({p.getAsString(), n});
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

    unsigned long getUnvisitedNodeCount() {
        return this->unvisited_map.size();
    }

};

#endif //MAZES_FOR_PROGRAMMERS_MAZE_H