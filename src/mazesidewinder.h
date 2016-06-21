#ifndef MAZES_FOR_PROGRAMMERS_MAZESIDEWINDER_H
#define MAZES_FOR_PROGRAMMERS_MAZESIDEWINDER_H

#include "maze.h"

class MazeSidewinder : public Maze {
private:
    /**
     * A dimensionally agnostic sidewinder maze algorithm
     */
    void generateAlgorithm() {

        std::vector<std::string> axis = this->getAllAxis();

        std::map<std::string, int> axisBias;
        for (auto axisIdentifier : axis) {
            axisBias.insert({axisIdentifier, this->getRandomNumber(0, 1)});
        }

        while (this->getUnvisitedNodeCount() > 0) {
            Node *workingNode = this->getRandomUnvisitedNode();
            Point workingPoint = workingNode->getPoint();

            std::vector<Node *> potentialNodes;

            std::vector<Node *> neighbourNodes = this->getNeighbourNodes(workingNode);
            for (auto neighbourNode : neighbourNodes) {
                for (auto axisIdentifier : axis) {
                    Point neighbour = neighbourNode->getPoint();
                    int axisValue = neighbour.getPositionOnAxis(axisIdentifier);
                    int workingNodeAxisValue = workingPoint.getPositionOnAxis(axisIdentifier);

                    //This greater than or less than size will define the bias of the maze
                    //Binary mazes will always have a "flat" side per axis, the < or > sign defines this
                    bool shouldAdd = false;
                    if (axisBias.at(axisIdentifier) == 0) {
                        if (axisValue > workingNodeAxisValue) {
                            shouldAdd = true;
                        }
                    } else {
                        if (axisValue < workingNodeAxisValue) {
                            shouldAdd = true;
                        }
                    }

                    if (shouldAdd) {
                        if (this->nodeExistsAtPoint(neighbour)) {
                            potentialNodes.push_back(neighbourNode);
                        }
                    }
                }
            }

            if (potentialNodes.size() >= 1) {
                unsigned long r = (unsigned long) this->getRandomNumber(0, (int) potentialNodes.size() - 1);

                Node *chosenNode = potentialNodes.at(r);

                workingNode->link(chosenNode);
            }

            this->markNodeAsVisited(workingNode);
        }
    }
};

#endif //MAZES_FOR_PROGRAMMERS_MAZESIDEWINDER_H
