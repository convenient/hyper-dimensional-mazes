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

            std::map<int, std::map<std::string, Node*>*> organisedNodes;

            //Sort the nodes to be organised by this axis, and the remaining sub-axis
            for (auto node : this->getMap()) {
                Node *n = node.second;
                if (this->nodeIsVisited(n)) {
                    continue;
                }
                Point tmpPoint = n->getPoint();

                int positionAtRowIdentifier = tmpPoint.getPositionOnAxis(rowIteratorAxisIdentifier);

                if (organisedNodes.count(positionAtRowIdentifier)) {
                    std::map<std::string, Node*> *nodesOnRow = organisedNodes.at(positionAtRowIdentifier);
                    nodesOnRow->insert({n->getPoint().getAsString(), n});
                } else {
                    std::map<std::string, Node*> *nodesOnRow = new std::map<std::string, Node*>();
                    nodesOnRow->insert({n->getPoint().getAsString(), n});
                    organisedNodes.insert({positionAtRowIdentifier, nodesOnRow});
                }
            }

            //TODO sort the inner arrays properly

            //Iterator over the nodes that have been organised in row and order
            //For each item in row
            for (auto element : organisedNodes) {
                std::vector<Node *> carvedPath;

                for (auto subMap : *element.second) {
                    Node *node = subMap.second;
                    std::cout << node->getPoint().getAsString() << std::endl;

                    carvedPath.push_back(node);

                    Point nextNodePoint = Point::getNeighbourPoint(node->getPoint(), rowIteratorAxisIdentifier, Point::negative);
                    if (!this->nodeExistsAtPoint(nextNodePoint)) {
                        //Handles the special case at the edge of the maze
                        //Draws the flat edge
                        this->processCarveSet(&carvedPath, nextAxisIdentifier);
                        continue;
                    }
//                    std::cout << "Should " << node->getPoint().getAsString() << " link to " << nextNodePoint.getAsString() << std::endl;

//                    if (this->getRandomNumber(0, 1)) {
//                        std::cout << "random\t\t" << node->getPoint().getAsString() << " -> " << nextNodePoint.getAsString() << std::endl;
//                        Node *nextNode = this->getNodeAtPoint(nextNodePoint);
//                        node->link(nextNode);
//                    } else {
//                        this->processCarveSet(&carvedPath, nextAxisIdentifier);
//                    }

                    this->markNodeAsVisited(node);
                }
                exit(0);
            }

        }
    }

    void processCarveSet(std::vector<Node *>* carvedPath, std::string axisIdentifier) {
        Node *randomNodeFromCarveSet = carvedPath->at(this->getRandomNumber(0, carvedPath->size()-1));

        Point tmpPoint = Point::getNeighbourPoint(randomNodeFromCarveSet->getPoint(), axisIdentifier, Point::positive);

        if (this->nodeExistsAtPoint(tmpPoint)) {

            Node *nextNode = this->getNodeAtPoint(tmpPoint);
            std::cout << "carveset\t" << randomNodeFromCarveSet->getPoint().getAsString() << " -> " << nextNode->getPoint().getAsString() << std::endl;
            randomNodeFromCarveSet->link(nextNode);
            carvedPath->clear();
        }
    }
};

#endif //MAZES_FOR_PROGRAMMERS_MAZESIDEWINDER_H
