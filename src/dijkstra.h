#ifndef MAZES_FOR_PROGRAMMERS_DIJKSTRA_H
#define MAZES_FOR_PROGRAMMERS_DIJKSTRA_H

#include "maze.h"
#include <algorithm>

class Dijkstra {
private:
    std::unordered_map<Node *, Node *> nodePath;
    std::unordered_map<Node *, Node *> nodeSolved;
    std::unordered_map<Node *, double> nodeDistances;
    std::vector<Node *> path;

    void setSolved(Node *node) {
        this->nodeSolved.insert({node, node});
    }

    bool isSolved(Node *node) {
        return (this->nodeSolved.count(node));
    }

    void setDistance(Node *node, double distance) {
        if (this->nodeDistances.count(node)) {
            this->nodeDistances.erase(node);
        }
        this->nodeDistances.insert({node, distance});
    }

    double getDistance(Node *node) {
        return this->nodeDistances.at(node);
    }

    void clearAll() {
        this->nodeDistances.clear();
        this->nodePath.clear();
        this->nodeSolved.clear();
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

        std::unordered_map<Node *, Node *> nodeNeighboursSolvedCache;

        bool solved = false;
        do {
            for (auto i : this->nodeSolved) {

                Node *workingNode = i.first;
                if (nodeNeighboursSolvedCache.count(workingNode)) {
                    continue;
                }

                Point workingPoint = workingNode->getPoint();

                bool nodeNeighboursSolved = true;

                Node *closestNode = nullptr;
                double closestDistance = 0;
                for (auto linkedNode : workingNode->getLinkedNodes()) {
                    if (!this->isSolved(linkedNode)) {
                        nodeNeighboursSolved = false;
                        double distance = workingPoint.getEuclideanDistanceTo(linkedNode->getPoint());
                        distance += this->getDistance(workingNode);

                        this->setDistance(linkedNode, distance);

                        if (closestNode == nullptr) {
                            closestNode = linkedNode;
                            closestDistance = distance;
                        } else if (distance < closestDistance) {
                            closestNode = linkedNode;
                            closestDistance = distance;
                        }

                        if (linkedNode == end) {
                            closestNode = linkedNode;
                            closestDistance = distance;
                            solved = true;
                            break;
                        }
                    }
                }

                if (nodeNeighboursSolved) {
                    nodeNeighboursSolvedCache.insert({workingNode, workingNode});
                }

                if (closestNode != nullptr) {
                    this->nodePath.insert({closestNode, workingNode});
                    this->setSolved(closestNode);
                    if (solved) {
                        //No need to continue looking through the linked nodes, we've got it!
                        break;
                    }
                }
            }
        } while (!solved);

        //Holy shit pointers to pointers.
        Node **workingNodePtrPtr = &end;
        while (true) {
            this->path.push_back(*workingNodePtrPtr);
            Node *workingNode = this->nodePath.at(*workingNodePtrPtr);
            workingNodePtrPtr = &workingNode;
            if (workingNode == start) {
                this->path.push_back(*workingNodePtrPtr);
                break;
            }
        }

        std::reverse(this->path.begin(), this->path.end());

        return this->path;
    }
};

#endif //MAZES_FOR_PROGRAMMERS_DIJKSTRA_H
