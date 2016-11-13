#ifndef MAZES_FOR_PROGRAMMERS_MAZEWILSONS_H
#define MAZES_FOR_PROGRAMMERS_MAZEWILSONS_H

#include "maze.h"
#include <map>

class MazeWilsons : public Maze {
    std::map<Node *, long> nodeToPosition;
    std::map<long, Node*> positionToNode;

    Node *secondLastNodeInWalk = nullptr;

    long positionCounter;

    void clearWalk() {
        this->nodeToPosition.clear();
        this->positionToNode.clear();
        this->positionCounter = 0;
    }

    void addToWalk(Node* node) {
        this->secondLastNodeInWalk = this->getLastNodeInWalk();
        this->positionCounter++;
        this->nodeToPosition.insert({node, this->positionCounter});
        this->positionToNode.insert({this->positionCounter, node});
    }

    void removeFromWalk(Node *node) {
        long position = this->nodeToPosition.at(node);
        this->nodeToPosition.erase(node);
        this->positionToNode.erase(position);
    }

    bool isInWalk(Node* node) {
        return (this->nodeToPosition.count(node));
    }

    Node* getLastNodeInWalk() {
        if (this->positionToNode.size() > 0) {
            return this->positionToNode.rbegin()->second;
        }
        return nullptr;
    }

    void trimWalkAfter(Node *node) {
        bool remove = false;

        std::vector<Node *> nodesToRemove;

        for (auto walkNodeMap : this->positionToNode) {
            Node* walkNode = walkNodeMap.second;
            if (remove) {
                nodesToRemove.push_back(walkNode);
            }
            if (walkNode == node) {
                remove = true;
            }
        }

        for (auto nodeToRemove : nodesToRemove) {
            this->removeFromWalk(nodeToRemove);
        }
    }

    void linkWalk() {
        Node *previousWalkNode = nullptr;
        for (auto walkNodeMap : this->positionToNode) {
            Node *walkNode = walkNodeMap.second;
            if (previousWalkNode == nullptr) {
                //This is the first walk through, we need to iterate over to the next section
            } else {
                this->markNodeAsVisited(previousWalkNode);
                this->linkNodes(walkNode, previousWalkNode);
            }
            previousWalkNode = walkNode;
        }
        Node *lastNodeInWalk = this->getLastNodeInWalk();
        //The last node in the walk may potentially be visited if this is a "collision" with an already visited section
        if (!this->nodeIsVisited(lastNodeInWalk)) {
            this->markNodeAsVisited(lastNodeInWalk);
        }
        this->clearWalk();
    }

public:
    std::string getName() {
        return "Wilsons";
    }

private:
    void generateAlgorithm() {

        Node *lastNodeAdded = nullptr;
        while (this->getUnvisitedNodeCount() > 0) {

            unsigned long count = this->getUnvisitedNodeCount();

            Node *targetNode;
            if (this->getVisitedNodesMap().empty()) {
                targetNode = this->getRandomUnvisitedNode();
            } else {
                targetNode = this->getRandomVisitedNode();
            }

            Node *initialWalkNode;
            while (true) {
                initialWalkNode = this->getRandomUnvisitedNode();
                //The initial walk node must be different from the target node
                if (initialWalkNode != targetNode) {
                    break;
                }
            }

            this->clearWalk();
            this->addToWalk(initialWalkNode);

            while (true) {

                Node *lastNodeInWalk = this->getLastNodeInWalk();
                Node *neighbour = this->getRandomNeighbourNode(lastNodeInWalk);

                //If we've hit a visited node then link to it
                //Just make sure we're not linking back to the first node in the walk, and ouroboros-ing this
                if ((neighbour == targetNode) || this->nodeIsVisited(neighbour)) {
                    lastNodeAdded = neighbour;
                    this->addToWalk(neighbour);
                    this->linkWalk();
                    break;
                }

                if (!this->isInWalk(neighbour)) {
                    this->addToWalk(neighbour);
                } else {
                    this->trimWalkAfter(neighbour);
                }
            }
        }
    }

    Node* getRandomNeighbourNode(Node *node) {
        Node *chosenNode = nullptr;
        while (true) {
            std::vector<Node *> neighbourNodes = this->getNeighbourNodes(node);
            unsigned long r = (unsigned long) this->getRandomNumber(0, (int) neighbourNodes.size() - 1);
            chosenNode = neighbourNodes.at(r);

            if (chosenNode != this->secondLastNodeInWalk) {
                break;
            }
        }
        return chosenNode;
    }
};

#endif //MAZES_FOR_PROGRAMMERS_MAZEWILSONS_H
