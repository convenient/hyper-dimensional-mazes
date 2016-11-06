#ifndef MAZES_FOR_PROGRAMMERS_4D_H
#define MAZES_FOR_PROGRAMMERS_4D_H

#include "convenient_maze.h"
#include "RendererText.h"
#include "solver.h"

int run(int argc, char **argv, Maze *mazePtr, st::string numberOfDimensions, std::string defaultSize) {

    convenient_maze::init(argc, argv, mazePtr, numberOfDimensions, defaultSize);
    convenient_maze::describeDimensions();

    Solver *solver = new Solver(mazePtr);

    convenient_maze::addNodesToMaze();
    mazePtr->generate();

    std::vector<Node *> path = solver->solve();
    RendererText::drawPath(path);

    return 0;
}

#endif //MAZES_FOR_PROGRAMMERS_4D_H
