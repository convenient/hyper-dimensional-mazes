#include <iostream>
#include "mazesidewinder.h"
#include "RendererText.h"
#include "solver.h"

int main(int argc, char **argv) {

    Maze *mazePtr = new MazeSidewinder;
    Solver *solver = new Solver(mazePtr);

    int mazeSize = 3;

    std::cout << "Generating a sidewinder maze of " << mazeSize << " by "<< mazeSize << " by " << mazeSize << " by " << mazeSize <<  std::endl;

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
