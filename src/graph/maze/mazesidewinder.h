#ifndef MAZES_FOR_PROGRAMMERS_MAZESIDEWINDER_H
#define MAZES_FOR_PROGRAMMERS_MAZESIDEWINDER_H

#include "maze.h"
#include <algorithm>

bool compareNodesByPoint(Node *a, Node *b) {
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

    throw std::logic_error(
            "These nodes are at the same exact point, this should never happen: " + aPoint.getAsString());
}

class MazeSidewinder : public Maze {
public:
    std::string getName() {
        return "Sidewinder";
    }

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

        /**
         * Backbone generation
         */
        std::string targetAxis = axis.front();
        std::vector<std::string> remainingAxis;
        for (auto axisIdentifier : axis) {
            if (axisIdentifier != targetAxis) {
                remainingAxis.push_back(axisIdentifier);
            }
        }

        int targetValueOnAxis = this->getRandomUnvisitedNode()->getPoint().getPositionOnAxis(targetAxis);
        for (auto nodeMapPtr : this->getMap()) {
            Node *n = nodeMapPtr.second;
            int pos = n->getPoint().getPositionOnAxis(targetAxis);
            if (pos < targetValueOnAxis) {
                targetValueOnAxis = pos;
            }
        }

        this->generateBackbone(targetAxis, targetValueOnAxis);

        //Iterator over the nodes that have been organised in row and order
        //For each item in row
        std::vector<Node *> carvedPath;
        for (auto node : sortedNodes) {

            if (this->isBackboneNode(node, targetAxis, targetValueOnAxis)) {
                continue; //backbone is processed separately
            }

            if (this->getUnvisitedNodeCount() <= 0) {
                break;
            }
            this->markNodeAsVisited(node);

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

            if (potentialPoints.size() > 0 && this->getRandomNumber(0, 1)) {
                Node *nextNode = this->getNodeAtPoint(potentialPoints.front());
                this->linkNodes(node, nextNode);
            } else {
                this->processCarveSet(&carvedPath, axis);
            }
        }
    }

    void processCarveSet(std::vector<Node *> *carvedPath, std::vector<std::string> axisList) {
        if (carvedPath->empty()) {
            return;
        }

        std::random_shuffle(carvedPath->begin(), carvedPath->end());

        for (auto randomNodeFromCarveSet : *carvedPath) {
            for (auto axisIdentifier : axisList) {
                Point tmpPoint = Point::getNeighbourPoint(randomNodeFromCarveSet->getPoint(), axisIdentifier,
                                                          Point::negative);
                if (this->nodeExistsAtPoint(tmpPoint)) {
                    Node *nextNode = this->getNodeAtPoint(tmpPoint);
                    this->linkNodes(randomNodeFromCarveSet, nextNode);
                    carvedPath->clear();
                    return;
                }
            }
        }
    }

    bool isBackboneNode(Node *n, std::string targetAxis, int targetValueOnAxis) {
        return (n->getPoint().getPositionOnAxis(targetAxis) == targetValueOnAxis);
    }

    void generateBackbone(std::string targetAxis, int targetValueOnAxis) {

        for (auto nodeMapPtr : this->getMap()) {
            Node *n = nodeMapPtr.second;
            if (!this->isBackboneNode(n, targetAxis, targetValueOnAxis)) {
                continue;
            }
            for (auto neighbourNode : this->getNeighbourNodes(n)) {
                if (this->isBackboneNode(neighbourNode, targetAxis, targetValueOnAxis)) {
                    this->linkNodes(neighbourNode, n);
                    if (!this->nodeIsVisited(neighbourNode)) {
                        this->markNodeAsVisited(neighbourNode);
                    }
                }
            }
            if (!this->nodeIsVisited(n)) {
                this->markNodeAsVisited(n);
            }
        }
    }
};

#endif //MAZES_FOR_PROGRAMMERS_MAZESIDEWINDER_H

