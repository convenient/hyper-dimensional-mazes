#ifndef MAZES_FOR_PROGRAMMERS_MAZEBINARY_H
#define MAZES_FOR_PROGRAMMERS_MAZEBINARY_H

#include "maze.h"

class MazeBinary : public Maze {
public:
    std::string getName() {
        return "Binary";
    }
private:
    /**
     * A dimensionally agnostic binary maze algorithm with a bias towards the positive axis
     */
    void generateAlgorithm() {

        std::vector<std::string> axis = this->getAllAxis();

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
                    //> == to the top right
                    //< == to the bottom left
                    //Todo find programattic way of varying the axis bias
                    if (axisValue > workingNodeAxisValue) {
                        if (this->nodeExistsAtPoint(neighbour)) {
                            potentialNodes.push_back(neighbourNode);
                        }
                    }
                }
            }

            if (potentialNodes.size() >= 1) {
                unsigned long r = (unsigned long) this->getRandomNumber(0, (int) potentialNodes.size() - 1);

                Node *chosenNode = potentialNodes.at(r);

                this->linkNodes(workingNode, chosenNode);
            }

            this->markNodeAsVisited(workingNode);
        }
    }
};

#endif //MAZES_FOR_PROGRAMMERS_MAZEBINARY_H
