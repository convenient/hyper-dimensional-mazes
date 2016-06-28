#ifndef MAZES_FOR_PROGRAMMERS_DIJKSTRA_H
#define MAZES_FOR_PROGRAMMERS_DIJKSTRA_H

#include "maze.h"
#include <algorithm>

class Dijkstra {
private:
    std::unordered_map<Node *, Node *> nodePath;
    std::unordered_map<Node *, Node *> nodeSolved;
    std::unordered_map<Node *, double> nodeDistances;

    unsigned long numberOfNodes;

    unsigned long getNumberOfNodes() {
        return this->numberOfNodes;
    }

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
    }

    std::vector<Node *> generateSolvedPath(Node *start, Node *end) {
        std::vector<Node *> path;

        //Holy shit pointers to pointers.
        Node **workingNodePtrPtr = &end;
        while (true) {
            path.push_back(*workingNodePtrPtr);
            Node *workingNode = this->nodePath.at(*workingNodePtrPtr);
            workingNodePtrPtr = &workingNode;
            if (workingNode == start) {
                path.push_back(*workingNodePtrPtr);
                break;
            }
        }

        std::reverse(path.begin(), path.end());
        return path;
    }

public:

    void setNumberOfNodes(unsigned long number) {
        this->numberOfNodes = number;
    }

    /**
     * Returns a vector containing node pointers journeying from the start point to the end point
     * Including both the start point and the end point.
     *
     * This means the shortest path will always be 2 in size, both a start and an end.
     */
    std::vector<Node *> getPath(Node *start, Node *end) {
        std::vector<Node *> endVector;
        endVector.push_back(end);
        std::unordered_map<Node *, std::vector<Node *>> endNodesSolutions = this->getPath(start, endVector);

        return endNodesSolutions.at(end);
    }

    /**
     * Modification of dijkstras algorithm to support finding 1 node to many end nodes. This is to ease the
     * computational expense of the all-pairs all paths problem.
     *
     * If we're searching from Node A to Nodes X,Y,Z they may share part of a common path. This should help sort
     * out these commonalities partly
     *
     */
    std::unordered_map<Node *, std::vector<Node *>> getPath(Node *start, std::vector<Node *> ends) {
        this->clearAll();

        this->setDistance(start, 0);
        this->setSolved(start);

        //Convert the end nodes vector into something more usable
        std::unordered_map<Node *, Node *> endNodesPending;
        std::unordered_map<Node *, std::vector<Node *>> endNodesPaths;

        for (auto end : ends) {
            if (!endNodesPending.count(end)) {
                endNodesPending.insert({end, nullptr});
            }
        }

        unsigned long failureCount = 0;

        while (!endNodesPending.empty()) {
            for (auto solvedNodeAutoIterator : this->nodeSolved) {

                Node *workingNode = solvedNodeAutoIterator.first;
                Point workingPoint = workingNode->getPoint();

                Node *closestNode = nullptr;
                double closestDistance = 0;
                for (auto linkedNode : workingNode->getLinkedNodes()) {
                    if (!this->isSolved(linkedNode)) {
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
                    }
                }

                if (closestNode != nullptr) {
                    this->nodePath.insert({closestNode, workingNode});
                    this->setSolved(closestNode);

                    if (endNodesPending.count(closestNode)) {
                        std::vector<Node *> path = this->generateSolvedPath(start, closestNode);
                        endNodesPending.erase(closestNode);
                        endNodesPaths.insert({closestNode, path});
                    }
                }

            }

            failureCount++;
            if (failureCount >= this->getNumberOfNodes()) {
                throw std::logic_error("Cannot find path, not all nodes are connected.");
            }
        }

        return endNodesPaths;
    }
};

#endif //MAZES_FOR_PROGRAMMERS_DIJKSTRA_H
