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

    throw std::logic_error("These nodes are at the same exact point, this should never happen");
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

        //Iterator over the nodes that have been organised in row and order
        //For each item in row
        bool firstRow = true;
        std::vector<Node *> carvedPath;
        Node *previousNode = nullptr;
        for (auto node : sortedNodes) {

            if (this->getUnvisitedNodeCount() <= 0) {
                break;
            }
            this->markNodeAsVisited(node);

            //Modification to support n dimensions
            if (previousNode != nullptr) {
                bool neighbourNode = false;
                Point previousPoint = previousNode->getPoint();
                for (auto neighbourPoint : node->getPoint().getNeighbouringPoints()) {
                    if (neighbourPoint.getEuclideanDistanceTo(previousPoint) == 0) {
                        neighbourNode = true;
                    }
                }
                if (!neighbourNode) {
                    if (!carvedPath.empty()) {
                        this->processCarveSet(&carvedPath, axis);
                    }
                }
            }

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

            if (firstRow && potentialPoints.size() <= 0) {
                firstRow = false;
            }

            if (firstRow || potentialPoints.size() > 0 && this->getRandomNumber(0, 1)) {
                Node *nextNode = this->getNodeAtPoint(potentialPoints.front());
                this->link(node, nextNode);
            } else {
                this->processCarveSet(&carvedPath, axis);
            }

            previousNode = node;
        }
    }

    void link(Node *a, Node *b) {
        a->link(b);
    }

    void processCarveSet(std::vector<Node *>* carvedPath, std::vector<std::string> axisList) {
        if (carvedPath->empty()) {
            std::cout << "carved path is empty" << std::endl;
            return;
        }

        std::random_shuffle(carvedPath->begin(), carvedPath->end());

        for (auto randomNodeFromCarveSet : *carvedPath) {
            for (auto axisIdentifier : axisList) {
                Point tmpPoint = Point::getNeighbourPoint(randomNodeFromCarveSet->getPoint(), axisIdentifier, Point::negative);
                if (this->nodeExistsAtPoint(tmpPoint)) {
                    Node *nextNode = this->getNodeAtPoint(tmpPoint);
                    this->link(randomNodeFromCarveSet, nextNode);
                    carvedPath->clear();
                    return;
                }
            }
        }
        std::cout << "FAIL TO CARVE " << std::endl;
    }
};

#endif //MAZES_FOR_PROGRAMMERS_MAZESIDEWINDER_H

