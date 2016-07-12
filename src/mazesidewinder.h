#ifndef MAZES_FOR_PROGRAMMERS_MAZESIDEWINDER_H
#define MAZES_FOR_PROGRAMMERS_MAZESIDEWINDER_H

#include "maze.h"
#include <algorithm>

bool compareNodesByPoint(Node* a, Node* b)
{
    //Nodes are the same, return false
    if (a == b) {
        return false;
    }

    Point aPoint = a->getPoint();
    Point bPoint = b->getPoint();

    std::vector<std::string> axis = Point::getAllAxis(aPoint, bPoint);

    for (auto axisIdentifier : axis) {
        int aVal = aPoint.getPositionOnAxis(axisIdentifier);
        int bVal = bPoint.getPositionOnAxis(axisIdentifier);
        if (aVal == bVal) {
            //These points are equal at this identifier, sk
            continue;
        }

        return (aVal < bVal);
    }

    std::cout << aPoint.getAsString() << std::endl;
    std::cout << bPoint.getAsString() << std::endl;

    std::cout << "These nodes are at the same exact point, this should never happen" << std::endl;
}

class MazeSidewinder : public Maze {
private:

    /**
     * http://stackoverflow.com/questions/1380463/sorting-a-vector-of-custom-objects
     */

    /**
     * A dimensionally agnostic sidewinder maze algorithm
     */
    void generateAlgorithm() {

        std::vector<std::string> axis = this->getAllAxis();

        std::vector<Node *> sortedNodes;
        for (auto node : this->getMap()) {
            Node *n = node.second;
            sortedNodes.push_back(n);
        }

        std::sort(sortedNodes.begin(), sortedNodes.end(), compareNodesByPoint);

        std::string firstAxis = axis.front();
        std::vector<std::string> remainingAxis;
        for (auto axisIdentifier : axis) {
            if (axisIdentifier != firstAxis) {
                remainingAxis.push_back(axisIdentifier);
            }
        }

        int rowPosition = sortedNodes.front()->getPoint().getPositionOnAxis(firstAxis);

        //Iterator over the nodes that have been organised in row and order
        //For each item in row
        bool firstRow = true;
        std::vector<Node *> carvedPath;
        for (auto node : sortedNodes) {
            if (this->getUnvisitedNodeCount() <= 0) {
                std::cout << "visited all nodes " << std::endl;
                break;
            }
            this->markNodeAsVisited(node);

            //else {
            carvedPath.push_back(node);

            std::vector<Point> potentialPoints;
            for (auto axisIdentifier : remainingAxis) {
                Point nextNodePoint = Point::getNeighbourPoint(node->getPoint(), axisIdentifier, Point::positive);
                if (this->nodeExistsAtPoint(nextNodePoint)) {
                    if (!this->nodeIsVisited(this->getNodeAtPoint(nextNodePoint))) {
                        potentialPoints.push_back(nextNodePoint);
                    }
                }
            }

            if (firstRow) {
                if (potentialPoints.size() > 0) {
                    Node *nextNode = this->getNodeAtPoint(potentialPoints.front());
                    std::cout << "first row linking " << node->getPoint().getAsString() << " -> " << nextNode->getPoint().getAsString() << std::endl;
                    node->link(nextNode);
                } else {
                    firstRow = false;
                    std::cout << "FIRST ROW DONE " << std::endl;
                }
                continue;
            }

            if (potentialPoints.size() <= 0) {
                std::cout << "No viable neighbours for " << node->getPoint().getAsString() << std::endl;
//                std::cout << carvedPath.size() << " < carveset size" << std::endl;
            }

            if (potentialPoints.size() > 0 && this->getRandomNumber(0, 1)) {
                Node *nextNode = this->getNodeAtPoint(potentialPoints.front());
                node->link(nextNode);
            } else {
                this->processCarveSet(&carvedPath, firstAxis);
            }

            int nodeRowPosition = node->getPoint().getPositionOnAxis(firstAxis);
            if (nodeRowPosition != rowPosition) {
                rowPosition = nodeRowPosition;
//                std::cout << carvedPath.size() << " < carveset size" << std::endl;
                carvedPath.clear();
//                this->processCarveSet(&carvedPath, firstAxis);
            }

        }
    }

    void processCarveSet(std::vector<Node *>* carvedPath, std::string axisIdentifier) {
        Node *randomNodeFromCarveSet = carvedPath->at(this->getRandomNumber(0, carvedPath->size()-1));
        carvedPath->clear();

        Point tmpPoint = Point::getNeighbourPoint(randomNodeFromCarveSet->getPoint(), axisIdentifier, Point::negative);

        if (this->nodeExistsAtPoint(tmpPoint)) {

            Node *nextNode = this->getNodeAtPoint(tmpPoint);
            randomNodeFromCarveSet->link(nextNode);
        } else {
            std::cout << "FAIL TO CARVE " << randomNodeFromCarveSet->getPoint().getAsString() << " failed to " << tmpPoint.getAsString() << std::endl;
            //TODO figure out this
//            std::cout << "Carve set failure!" << std::endl;
        }
    }
};

#endif //MAZES_FOR_PROGRAMMERS_MAZESIDEWINDER_H

