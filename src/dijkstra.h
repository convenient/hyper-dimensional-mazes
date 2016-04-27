#ifndef MAZES_FOR_PROGRAMMERS_DIJKSTRA_H
#define MAZES_FOR_PROGRAMMERS_DIJKSTRA_H

#include "maze.h"

class Dijkstra {
private:
    std::unordered_map<Node *, Node *> nodeSolved;
    std::unordered_map<Node *, double> nodeDistances;
    std::vector<Node *> path;

    void setSolved(Node *node) {
        this->nodeSolved.insert({node, node});
    }

    bool isSolved(Node *node) {
        return (this->nodeSolved.at(node));
    }

    void setDistance(Node *node, double distance) {
        if (this->nodeDistances.at(node)) {
            this->nodeDistances.erase(node);
        }
        this->nodeDistances.insert({node, distance});
    }

    double getDistance(Node *node) {
        return this->nodeDistances.at(node);
    }

    void clearAll() {
        this->nodeDistances.clear();
        this->path.clear();
    }

public:
    /**
     * Returns a vector containing node pointers journeying from the start point to the end point
     * Including both the start point and the end point.
     *
     * This means the shortest path will always be 2 in size, both a start and an end.
     */
    std::vector<Node *> getPath(Node *start, Node *end) {
        this->clearAll();

        this->setDistance(start, 0);
        this->setSolved(start);

        for (auto i : this->nodeSolved) {

            Node *workingNode = i.first;
            Point workingPoint = workingNode->getPoint();

            Node closestNode = nullptr;
            double closestDistance = 0;
            for (auto linkedNode : workingNode->getLinkedNodes()) {
                if (this->isSolved(linkedNode)) {

                } else {
                    double distance = workingPoint.getEuclideanDistanceTo(linkedNode->getPoint());
                    //TODO Work out the length of the arc
                    this->setDistance(linkedNode, distance);

                    if (closestNode == nullptr) {
                        closestNode = linkedNode;
                        closestDistance = distance;
                    } else if (distance < closestDistance) {
                        closestDistance = linkedNode;
                        closestDistance = distance;
                    }
                }
            }
            this->setSolved(closestNode);
        }

        return path;
    }
};

#endif //MAZES_FOR_PROGRAMMERS_DIJKSTRA_H
