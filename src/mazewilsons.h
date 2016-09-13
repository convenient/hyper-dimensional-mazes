#ifndef MAZES_FOR_PROGRAMMERS_MAZEWILSONS_H
#define MAZES_FOR_PROGRAMMERS_MAZEWILSONS_H

#include "maze.h"
#include <map>

class MazeWilsons : public Maze {
    std::map<Node *, long> nodeToPosition;
    std::map<long, Node*> positionToNode;

    long positionCounter;

    void clearWalk() {
        this->nodeToPosition.clear();
        this->positionToNode.clear();
        this->positionCounter = 0;
    }

    void addToWalk(Node* node) {
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
        return this->positionToNode.rbegin()->second;
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
            if (!this->nodeIsVisited(walkNode)) {
                this->markNodeAsVisited(walkNode);
            }

            if (previousWalkNode == nullptr) {
                //This is the first walk through, we need to iterate over to the next section
            } else {
                walkNode->link(previousWalkNode);
            }
            previousWalkNode = walkNode;
        }
        this->clearWalk();
    }

    void debugWalk() {
        if (this->nodeToPosition.size() != this->positionToNode.size()) {
            exit(-99);
        }

        for (auto walkNodeMap : this->positionToNode) {
            unsigned long pos1 = walkNodeMap.first;
            Node *debug = walkNodeMap.second;
            unsigned long pos2 = this->nodeToPosition.at(debug);
            if (pos1 != pos2) {
                exit(-44);
            }
            std::cout << "\t" << pos1 << "\t" << debug->getPoint().getAsString() << std::endl;
        }
    }




private:
    void generateAlgorithm() {


        while (this->getUnvisitedNodeCount() > 0) {



            std::cout << "##################################################" << this->getUnvisitedNodeCount() << std::endl;
            Node *targetNode = this->getRandomUnvisitedNode();
            std::cout << "Target node\t\t\t" << targetNode->getPoint().getAsString() << std::endl;

            if (targetNode->getPoint().getAsString() == "(x:-1)(y:-1)") {
                int lol = 1;
            }

            Node *initialWalkNode;
            while (true) {
                if (this->getUnvisitedNodeCount() <= 2) {
                    initialWalkNode = this->getRandomVisitedNode();
                } else {
                    initialWalkNode = this->getRandomUnvisitedNode();
                }
                if (initialWalkNode != targetNode) {
                    this->markNodeAsVisited(initialWalkNode);
                    break;
                }
            }

            this->clearWalk();

            this->addToWalk(initialWalkNode);
            this->debugWalk();
            std::cout << "Starting walk!" << std::endl;
            while (true) {
                std::cout << "------------walking--------------" << std::endl;

                Node *lastNodeInWalk = this->getLastNodeInWalk();
                std::cout << "last node from walk\t" << lastNodeInWalk->getPoint().getAsString() << std::endl;
                Node *neighbour = this->getRandomNeighbourNode(lastNodeInWalk);
                std::cout << "random neighbour node\t" << neighbour->getPoint().getAsString() << std::endl;
                if (this->nodeIsVisited(neighbour)) {
                    std::cout << "linking!" << std::endl;
                    this->addToWalk(neighbour);
                    this->linkWalk();
                    std::cout << "linked" << std::endl;
                    break;
                }

                if (!this->isInWalk(neighbour)) {
                    std::cout << "adding to walk\t" << neighbour->getPoint().getAsString();
                    this->addToWalk(neighbour);
                    std::cout << "\tdone" << std::endl;
                } else {
                    std::cout << "closing loop ";
                    this->trimWalkAfter(neighbour);
                    std::cout << "\tdone" << std::endl;
                }

                this->debugWalk();
            }
        }
    }

    Node* getRandomNeighbourNode(Node *node) {
        std::vector<Node *> neighbourNodes = this->getNeighbourNodes(node);
        unsigned long r = (unsigned long) this->getRandomNumber(0, (int) neighbourNodes.size() - 1);
        Node *chosenNode = neighbourNodes.at(r);
        return chosenNode;
    }
};

#endif //MAZES_FOR_PROGRAMMERS_MAZEWILSONS_H
