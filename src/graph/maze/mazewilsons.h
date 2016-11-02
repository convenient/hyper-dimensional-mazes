#ifndef MAZES_FOR_PROGRAMMERS_MAZEWILSONS_H
#define MAZES_FOR_PROGRAMMERS_MAZEWILSONS_H

#include <iostream>
//debugging
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
                std::cout << previousWalkNode->getPoint().getAsString() << "\tlinking to\t" << walkNode->getPoint().getAsString() << std::endl;
                this->markNodeAsVisited(previousWalkNode);
                this->linkNodes(walkNode, previousWalkNode);
            }
            previousWalkNode = walkNode;
        }
        Node *lastNodeInWalk = this->getLastNodeInWalk();
        //The last node in the walk may potentially be visitied if this is a "collision" with an already visited section
        if (!this->nodeIsVisited(lastNodeInWalk)) {
            this->markNodeAsVisited(lastNodeInWalk);
        }
        this->clearWalk();
    }

    void debugWalk() {
        for (auto walkNodeMap : this->positionToNode) {
            unsigned long pos1 = walkNodeMap.first;
            Node *debug = walkNodeMap.second;
            std::cout << "\t" << pos1 << "\t" << debug->getPoint().getAsString() << std::endl;
        }
    }
public:
    std::string getName() {
        return "Wilsons";
    }

private:
    void generateAlgorithm() {

        Node *lastNodeAdded = nullptr;
        while (this->getUnvisitedNodeCount() > 0) {

            std::cout << "##################################################" << this->getUnvisitedNodeCount() << std::endl;
            Node *targetNode = this->getRandomUnvisitedNode();
            std::cout << "Target node\t\t\t" << targetNode->getPoint().getAsString() << std::endl;

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
            this->debugWalk();
            std::cout << "Starting walk!" << std::endl;
            while (true) {
                std::cout << "------------walking--------------" << std::endl;

                Node *lastNodeInWalk = this->getLastNodeInWalk();
                std::cout << "last node from walk\t" << lastNodeInWalk->getPoint().getAsString() << std::endl;
                Node *neighbour = this->getRandomNeighbourNode(lastNodeInWalk);
                std::cout << "random neighbour node\t" << neighbour->getPoint().getAsString() << std::endl;

                //If we've hit a visited node then link to it
                //Just make sure we're not linking back to the first node in the walk, and ouroboros-ing this
                if ((neighbour == targetNode) || this->nodeIsVisited(neighbour)) {
                    std::cout << "linking!" << std::endl;
                    lastNodeAdded = neighbour;
                    this->addToWalk(neighbour);
                    this->debugWalk();
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

        //A supermassive hack hole, because the maze was not finishing off properly and was leaving an unlined island :(
        //This would mean that not all the maze is connected.
        while (true) {
            std::vector<Node *> neighbourNodes = this->getNeighbourNodes(lastNodeAdded);
            unsigned long r = (unsigned long) this->getRandomNumber(0, (int) neighbourNodes.size() - 1);
            Node *chosenNode = neighbourNodes.at(r);

            if (!lastNodeAdded->isLinked(chosenNode)) {
                lastNodeAdded->link(chosenNode);
                break;
            }
        }


        std::cout << "DONE" << std::endl;
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
