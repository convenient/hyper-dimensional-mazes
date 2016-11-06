#ifndef MAZES_FOR_PROGRAMMERS_2D_GRID_H
#define MAZES_FOR_PROGRAMMERS_2D_GRID_H

#include "convenient_maze.h"
#include <iostream>
#include "RendererText.h"
#include "solver.h"
#include "RendererGrid3D.h"

bool showTextSolution = false;

void generateCallback(Maze *m, Solver *s) {
    showTextSolution = true;
    RendererText::drawNodeGoal(s->getStartNode(), s->getEndNode());
}

void solveCallback(Maze *m, Solver *s) {
    if (showTextSolution) {
        RendererText::drawPath(s->solve());
        showTextSolution = false;
    }
}

int run(int argc, char **argv, Maze *mazePtr, std::string numberOfDimensions, std::string defaultSize) {

    convenient_maze::init(argc, argv, mazePtr, numberOfDimensions, defaultSize);
    convenient_maze::describeDimensions();

    Solver *solver = new Solver(mazePtr);
    RendererGrid3D *rendererGridPtr =
            new RendererGrid3D(mazePtr, solver, convenient_maze::getTitleCharStar(), generateCallback, solveCallback);

    convenient_maze::addNodesToMaze();

    rendererGridPtr->startOpenGl();

    return 0;
}

#endif //MAZES_FOR_PROGRAMMERS_2D_GRID_H
