#ifndef MAZES_FOR_PROGRAMMERS_4D_H
#define MAZES_FOR_PROGRAMMERS_4D_H

#include <iostream>
#include "RendererText.h"
#include "solver.h"

int run(int argc, char **argv, Maze *mazePtr) {

    Solver *solver = new Solver(mazePtr);

    if (argc == 2) {
        unsigned long seed =  strtoul (argv[1], NULL, 0);
        mazePtr->setSeed(seed);
    }

    std::cout << "Using seed: " << mazePtr->getSeed() << std::endl;

    int mazeSize = 6;

    //todo sort this
    std::cout << "Generating a WHATEVER maze of " << mazeSize << " by "<< mazeSize << " by " << mazeSize << " by " << mazeSize <<  std::endl;

    for (int w=0; w< mazeSize; w++) {
        for (int x = 0; x < mazeSize; x++) {
            for (int y = 0; y < mazeSize; y++) {
                for (int z = 0; z < mazeSize; z++) {
                    Point p;
                    p.addPosition("w", w);
                    p.addPosition("x", x);
                    p.addPosition("y", y);
                    p.addPosition("z", z);
                    mazePtr->createNode(p);
                }
            }
        }
    }
    mazePtr->generate();

    std::vector<Node *> path = solver->solve();
    RendererText::drawPath(path);

    return 0;
}

#endif //MAZES_FOR_PROGRAMMERS_4D_H
