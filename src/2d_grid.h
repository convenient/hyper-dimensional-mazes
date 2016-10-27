#ifndef MAZES_FOR_PROGRAMMERS_2D_GRID_H
#define MAZES_FOR_PROGRAMMERS_2D_GRID_H

#include <iostream>
#include "Render/RendererText.h"
#include "solver.h"
#include "Render/RendererGrid3D.h"

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

int run(int argc, char **argv, Maze *mazePtr) {

    Solver *solver = new Solver(mazePtr);

    if (argc == 2) {
        unsigned long seed =  strtoul (argv[1], NULL, 0);
        mazePtr->setSeed(seed);
    }

    //todo make this dynamic
    char title[] = "WHATEVER Maze - 2D Grid";
    RendererGrid3D *rendererGridPtr = new RendererGrid3D(mazePtr, solver, title, generateCallback, solveCallback);

    int mazeSize = 18;
    //Offset the node position to make rendering easier and map to nice opengl stuff.
    int minpart = (int)floor(mazeSize/2) * -1;
    int maxpart = (int)ceil(mazeSize/2);

    //todo this too
    std::cout << "Generating a WHATEVER maze of " << mazeSize << " by " << mazeSize << std::endl;

    for (int x=minpart; x<maxpart; x++) {
        for (int y=minpart; y<maxpart; y++) {
            Point p;
            p.addPosition("x", x);
            p.addPosition("y", y);
            mazePtr->createNode(p);
        }
    }

    rendererGridPtr->startOpenGl();

    return 0;
}

#endif //MAZES_FOR_PROGRAMMERS_2D_GRID_H
