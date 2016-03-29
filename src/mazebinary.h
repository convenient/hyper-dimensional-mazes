#ifndef MAZES_FOR_PROGRAMMERS_MAZEBINARY_H
#define MAZES_FOR_PROGRAMMERS_MAZEBINARY_H

#include "maze.h"

class MazeBinary : public Maze {
public:
    void generate() {

        std::vector<std::string> axis = this->getAllAxis();

        while (this->getUnvisitedNodeCount() > 0) {
            Node *workingNode = this->getRandomUnvisitedNode();
            Point workingPoint = workingNode->getPoint();

            std::vector<Point> potentialPoints;

            for (auto axisIdentifier : axis) {
                Point p = Point::getNeighbourPoint(workingPoint, axisIdentifier, Point::positive);

                if (this->nodeExistsAtPoint(p)) {
                    potentialPoints.push_back(p);
                }
            }

            if (potentialPoints.size() >= 1) {
                unsigned long r = (unsigned long) this->getRandomNumber(0, (int) potentialPoints.size() - 1);

                Point chosenPoint = potentialPoints.at(r);
                this->connectNodes(workingPoint, chosenPoint);
            }

            this->markNodeAsVisited(workingNode);
        }
    }
};

#endif //MAZES_FOR_PROGRAMMERS_MAZEBINARY_H
