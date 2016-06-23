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

        //Work out the "limits" or the maze
        for(std::vector<int>::size_type i = 0; i != axis.size(); i++) {
            if (axis.size() <= i+1 ) {
                break;
            }
            std::string rowIteratorAxisIdentifier = axis[i];
            std::string nextAxisIdentifier = axis[i+1];
            std::cout << rowIteratorAxisIdentifier << "," << nextAxisIdentifier << std::endl;

            int rowIteratorMax = this->getMap().begin()->second->getPoint().getPositionOnAxis(rowIteratorAxisIdentifier);
            int rowIteratorMin = this->getMap().begin()->second->getPoint().getPositionOnAxis(rowIteratorAxisIdentifier);

            int rowEdgeNumber = this->getMap().begin()->second->getPoint().getPositionOnAxis(nextAxisIdentifier);
            for (auto node : this->getMap()) {
                Node *n = node.second;
                Point tmpPoint = n->getPoint();
                int rowIteratorPositionOn = tmpPoint.getPositionOnAxis(rowIteratorAxisIdentifier);
                int positionOnAxis = tmpPoint.getPositionOnAxis(nextAxisIdentifier);
                if (positionOnAxis < rowEdgeNumber) {
                    rowEdgeNumber = positionOnAxis;
                    rowIteratorMax = rowIteratorPositionOn;
                    rowIteratorMin = rowIteratorPositionOn;
                    continue;
                } else if (positionOnAxis == rowEdgeNumber) {
                    if (rowIteratorMax < rowIteratorPositionOn) {
                        rowIteratorMax = rowIteratorPositionOn;
                    } else if (rowIteratorMin > rowIteratorPositionOn) {
                        rowIteratorMin = rowIteratorPositionOn;
                    }
                }
            }

            //Group the nodes by edge Number

            std::cout << rowIteratorMin << "," << rowEdgeNumber << std::endl;
            std::cout << rowIteratorMax << "," << rowEdgeNumber << std::endl;

        }

        exit(0);

        std::string rowIteratorIdentifier = axis.at(0);

        std::cout << rowIteratorIdentifier << std::endl;

        //TODO make this agnostic
        //Get largest Y, add all for that Y into that set, sort them by X
        // Iterate through those as equal to "work through row grid wise"
        Point point;
        point.addPosition("x", -9);
        point.addPosition("y", -9);

        Node *startNode = this->getNodeAtPoint(point);
        this->markNodeAsVisited(startNode);

        Node *currentNode;
        while (this->getUnvisitedNodeCount() > 0) {

            bool finishedRow = false;
            Point p = currentNode->getPoint();

            Point nextPointOnAxis = Point::getNeighbourPoint(p, rowIteratorIdentifier, Point::positive);
            if (this->nodeExistsAtPoint(nextPointOnAxis)) {
                Node *nextNodeOnRow = this->getNodeAtPoint(nextPointOnAxis);
                std::cout << nextNodeOnRow->getPoint().getAsString() << std::endl;
            }

//http://weblog.jamisbuck.org/2011/2/3/maze-generation-sidewinder-algorithm
//        Work through the grid row-wise, starting with the cell at 0,0. Initialize the “run” set to be empty.
//                Add the current cell to the “run” set.
//                For the current cell, randomly decide whether to carve east or not.
//        If a passage was carved, make the new cell the current cell and repeat steps 2-4.
//        If a passage was not carved, choose any one of the cells in the run set and carve a passage north. Then empty the run set, set the next cell in the row to be the current cell, and repeat steps 2-5.
//        Continue until all rows have been processed.


            exit(0);

        }
    }
};

#endif //MAZES_FOR_PROGRAMMERS_MAZESIDEWINDER_H
