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

private:
    void generateAlgorithm() {


        while (this->getUnvisitedNodeCount() > 0) {
            std::cout << "##################################################" << std::endl;
            Node *targetNode = this->getRandomUnvisitedNode();
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
            while (true) {
                std::cout << "##############" << std::endl;

                Node *lastNodeInWalk = this->getLastNodeInWalk();
                std::cout << "last node in walk " << lastNodeInWalk->getPoint().getAsString() << std::endl;
                Node *neighbour = this->getRandomNeighbourNode(lastNodeInWalk);

                if (this->nodeIsVisited(neighbour)) {
                    std::cout << "linking!" << std::endl;
                    this->addToWalk(neighbour);
                    this->linkWalk();
                    std::cout << "linked" << std::endl;
                    break;
                }

                if (!this->isInWalk(neighbour)) {
                    std::cout << "adding to walk " << neighbour->getPoint().getAsString() << std::endl;
                    this->addToWalk(neighbour);
                    std::cout << "added " << std::endl;
                } else {
                    std::cout << "closing loop " << std::endl;
                    this->trimWalkAfter(neighbour);
                    std::cout << "closed " << std::endl;

                }
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
