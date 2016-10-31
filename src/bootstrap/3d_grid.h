#ifndef MAZES_FOR_PROGRAMMERS_2D_GRID_H
#define MAZES_FOR_PROGRAMMERS_2D_GRID_H

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

int run(int argc, char **argv, Maze *mazePtr) {

    Solver *solver = new Solver(mazePtr);

    if (argc == 2) {
        unsigned long seed =  strtoul (argv[1], NULL, 0);
        mazePtr->setSeed(seed);
    }

    std::string titleString = mazePtr->getName() + " Maze - 3D Grid";
    char *title = new char[titleString.length() + 1];
    strcpy(title, titleString.c_str());

    RendererGrid3D *rendererGridPtr = new RendererGrid3D(mazePtr, solver, title, generateCallback, solveCallback);

    int mazeSize = 10;
    //Offset the node position to make rendering easier and map to nice opengl stuff.
    int minpart = (int)floor(mazeSize/2) * -1;
    int maxpart = (int)ceil(mazeSize/2);

    std::cout << "Generating a " + mazePtr->getName() + " maze of " << mazeSize << " by " << mazeSize << " by " << mazeSize << std::endl;

    for (int x=minpart; x<maxpart; x++) {
        for (int y=minpart; y<maxpart; y++) {
            for (int z=minpart; z<maxpart; z++) {
                Point p;
                p.addPosition("x", x);
                p.addPosition("y", y);
                p.addPosition("z", z);
                mazePtr->createNode(p);
            }
        }
    }

    rendererGridPtr->startOpenGl();

    return 0;
}

#endif //MAZES_FOR_PROGRAMMERS_2D_GRID_H