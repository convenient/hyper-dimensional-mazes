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
        for (auto walkNodeMap : this->positionToNode) {
            Node* walkNode = walkNodeMap.second;
            if (remove) {
                this->removeFromWalk(walkNode);
            }
            if (walkNode == node) {
                remove = true;
            }
        }
    }

    void linkWalk() {
        Node *previousWalkNode = nullptr;
        for (auto walkNodeMap : this->positionToNode) {
            Node *walkNode = walkNodeMap.second;

            if (previousWalkNode == nullptr) {
                //This is the first walk through, we need to iterate over to the next section
            } else {
                walkNode->link(previousWalkNode);
            }
            previousWalkNode = walkNode;
        }
    }

    void debugWalk() {
        std::cout << "\t" << "pos to node" << std::endl;
        for (auto walkNodeMap : this->positionToNode) {
            std::cout << "\t" << walkNodeMap.first << "\t" << walkNodeMap.second->getPoint().getAsString() << std::endl;
        }

        std::cout << "\t" <<  "node to pos" << std::endl;
        for (auto walkNodeMap : this->nodeToPosition) {
            std::cout << "\t" << walkNodeMap.second << "\t" << walkNodeMap.first->getPoint().getAsString() << std::endl;
        }
    }


private:
    void generateAlgorithm() {


        while (this->getUnvisitedNodeCount() > 0) {
            std::cout << "##################################################" << std::endl;
            Node *targetNode = this->getRandomUnvisitedNode();
            std::cout << "Target node\t\t\t" << targetNode->getPoint().getAsString() << std::endl;
            this->markNodeAsVisited(targetNode);

            Node *initialWalkNode;
            while (true) {
                initialWalkNode = this->getRandomUnvisitedNode();
                if (initialWalkNode != targetNode) {
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
