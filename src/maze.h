#ifndef MAZES_FOR_PROGRAMMERS_MAZE_H
#define MAZES_FOR_PROGRAMMERS_MAZE_H

#include "node.h"
#include <random>
#include <string>
#include <chrono>

class Maze {
    std::unordered_map<std::string, Node *> map;
    std::unordered_map<std::string, Node *> unvisited_map;

    std::mt19937 rng;
    bool rngSeeded = false;
    std::vector<std::string> axis;

    Node *getRandomNode(std::unordered_map<std::string, Node *> map) {

        if (map.size() < 1) {
            throw std::logic_error("Tried to get random node when none in maze");
        }

        int r = this->getRandomNumber(0, (int) map.size() - 1);

        //http://stackoverflow.com/a/27024374/4354325
        auto random_it = std::next(std::begin(map), r);

        std::string key = random_it->first;
        return map.at(key);
    }

    virtual void generateAlgorithm() = 0;

public:

    void generate() {
        /*
         * Reset all object caches etc
         */
        this->unvisited_map = map;
        this->axis.clear();
        for (auto nodeItr : this->getMap()) {
            Node *node = nodeItr.second;
            node->clearLinkedNodes();
        }
        //Generate a maze for the defined nodes!
        this->generateAlgorithm();
    }

    int getRandomNumber(int min, int max) {
        if (!this->rngSeeded) {
            typedef std::chrono::high_resolution_clock myclock;
            myclock::time_point beginning = myclock::now();

            myclock::duration d = myclock::now() - beginning;
            unsigned seed = d.count();

            this->rng.seed(seed);
            this->rngSeeded = true;
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
                return;
            }
        }
        throw std::logic_error("Tried to mark a node as visited when it does not exist");
    }

    Node *getRandomUnvisitedNode() {
        return this->getRandomNode(this->unvisited_map);
    };

    std::vector<Node *> getDeadEnds() {
        std::vector<Node *> deadEnds;

        for (auto nodeItr : this->getMap()) {
            Node *node = nodeItr.second;
            if (node->getLinkedNodes().size() == 1) {
                deadEnds.push_back(node);
            }
        }

        return deadEnds;
    }

    std::vector<std::string> getAllAxis() {

        if (this->axis.size() <=0) {
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
            this->axis = axis;
        }

        return this->axis;
    }

    Node *createNode(Point p) {
        if (this->nodeExistsAtPoint(p)) {
            throw std::logic_error("Tried to create a node where already exists");
        }

        Node *n = new Node(p);

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

    Node *getNodeAtPoint(Point p) {
        if (this->nodeExistsAtPoint(p)) {
            Node *node = this->map.at(p.getAsString());
            return node;
        }
        throw std::logic_error("Node does not exist at point");
    }

    std::unordered_map<std::string, Node *> getMap() {
        return this->map;
    }

    unsigned long getUnvisitedNodeCount() {
        return this->unvisited_map.size();
    }

    std::vector<Node *> getNeighbourNodes(Node *node) {
        Point point = node->getPoint();

        std::vector<Node *> neighbourNodes;

        std::vector<std::string> axis = this->getAllAxis();

        for (auto axisIdentifier : axis) {
            Point positive = Point::getNeighbourPoint(point, axisIdentifier, Point::positive);

            if (this->nodeExistsAtPoint(positive)) {
                neighbourNodes.push_back(this->getNodeAtPoint(positive));
            }

            Point negative = Point::getNeighbourPoint(point, axisIdentifier, Point::negative);

            if (this->nodeExistsAtPoint(negative)) {
                neighbourNodes.push_back(this->getNodeAtPoint(negative));
            }
        }
        return neighbourNodes;
    }

};

#endif //MAZES_FOR_PROGRAMMERS_MAZE_H
