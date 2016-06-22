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

        std::string rowIteratorIdentifier = axis.at(0);

        std::cout << rowIteratorIdentifier << std::endl;

        //TODO make this agnostic
        Point point;
        point.addPosition("x", -9);
        point.addPosition("y", -9);

        Node *startNode = this->getNodeAtPoint(point);

//http://weblog.jamisbuck.org/2011/2/3/maze-generation-sidewinder-algorithm
//        Work through the grid row-wise, starting with the cell at 0,0. Initialize the “run” set to be empty.
//                Add the current cell to the “run” set.
//                For the current cell, randomly decide whether to carve east or not.
//        If a passage was carved, make the new cell the current cell and repeat steps 2-4.
//        If a passage was not carved, choose any one of the cells in the run set and carve a passage north. Then empty the run set, set the next cell in the row to be the current cell, and repeat steps 2-5.
//        Continue until all rows have been processed.


                exit();
    }
};

#endif //MAZES_FOR_PROGRAMMERS_MAZESIDEWINDER_H
