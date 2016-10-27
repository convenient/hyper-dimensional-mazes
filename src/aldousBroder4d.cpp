#include <iostream>
#include "maze/mazealdousbroder.h"
#include "Render/RendererText.h"
#include "bootstrap/solver.h"

int main(int argc, char **argv) {

    Maze *mazePtr = new MazeAldousBroder;
    Solver *solver = new Solver(mazePtr);

    if (argc == 2) {
        unsigned long seed =  strtoul (argv[1], NULL, 0);
        mazePtr->setSeed(seed);
    }

    int mazeSize = 6;

    std::cout << "Generating a Aldous-Broder maze of " << mazeSize << " by "<< mazeSize << " by " << mazeSize << " by " << mazeSize <<  std::endl;

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
