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

        for(std::vector<int>::size_type i = 0; i != axis.size(); i++) {
            if (axis.size() <= i+1 ) {
                break;
            }
            std::string rowIteratorAxisIdentifier = axis[i];
            std::string nextAxisIdentifier = axis[i+1];

            std::map<int, std::map<int, Node*>*> organisedNodes;

            //Sort the nodes to be organised by this axis, and the remaining sub-axis
            for (auto node : this->getMap()) {
                Node *n = node.second;
                if (this->nodeIsVisited(n)) {
                    continue;
                }
                Point tmpPoint = n->getPoint();

                int positionAtRowIdentifier = tmpPoint.getPositionOnAxis(rowIteratorAxisIdentifier);

                if (organisedNodes.count(positionAtRowIdentifier)) {
                    std::map<int, Node*> *nodesOnRow = organisedNodes.at(positionAtRowIdentifier);
                    nodesOnRow->insert({n->getPoint().getPositionOnAxis(nextAxisIdentifier), n});
                } else {
                    std::map<int, Node*> *nodesOnRow = new std::map<int, Node*>();
                    nodesOnRow->insert({n->getPoint().getPositionOnAxis(nextAxisIdentifier), n});
                    organisedNodes.insert({positionAtRowIdentifier, nodesOnRow});
                }
            }

            bool firstRow = true;

            //Iterator over the nodes that have been organised in row and order
            //For each item in row
            for (auto element : organisedNodes) {
                std::vector<Node *> carvedPath;

                for (auto subMap : *element.second) {
                    Node *node = subMap.second;

                    //The first row is a special case and always forms a long column
                    if (firstRow) {
                        Point nextNodePoint = Point::getNeighbourPoint(node->getPoint(), nextAxisIdentifier, Point::positive);
                        if (this->nodeExistsAtPoint(nextNodePoint)) {
                            Node *nextNode = this->getNodeAtPoint(nextNodePoint);
                            node->link(nextNode);
                        }
                        continue;
                    }

                    carvedPath.push_back(node);

                    Point nextNodePoint = Point::getNeighbourPoint(node->getPoint(), nextAxisIdentifier, Point::positive);
                    if (!this->nodeExistsAtPoint(nextNodePoint)) {
                        this->processCarveSet(&carvedPath, rowIteratorAxisIdentifier);
                        continue;
                    }

                    if (this->getRandomNumber(0, 1)) {
                        Node *nextNode = this->getNodeAtPoint(nextNodePoint);
                        node->link(nextNode);
                    } else {
                        this->processCarveSet(&carvedPath, rowIteratorAxisIdentifier);
                    }

                    this->markNodeAsVisited(node);
                }
                firstRow = false;
            }

        }
    }

    void processCarveSet(std::vector<Node *>* carvedPath, std::string axisIdentifier) {
        Node *randomNodeFromCarveSet = carvedPath->at(this->getRandomNumber(0, carvedPath->size()-1));

        Point tmpPoint = Point::getNeighbourPoint(randomNodeFromCarveSet->getPoint(), axisIdentifier, Point::negative);

        if (this->nodeExistsAtPoint(tmpPoint)) {

            Node *nextNode = this->getNodeAtPoint(tmpPoint);
            randomNodeFromCarveSet->link(nextNode);
            carvedPath->clear();
        }
    }
};

#endif //MAZES_FOR_PROGRAMMERS_MAZESIDEWINDER_H
