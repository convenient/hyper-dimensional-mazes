#include <iostream>
#include "mazebinary.h"
#include "RendererText.h"
#include "Solver.h"
#include "RendererGrid3D.h"

void generateCallback(Maze *m, Solver *s) {
    RendererText::drawNodeGoal(s->getStartNode(), s->getEndNode());
}

void solveCallback(Maze *m, Solver *s) {
    RendererText::drawPath(s->solve());
}

int main(int argc, char **argv) {

    Maze *mazePtr = new MazeBinary;
    Solver *solver = new Solver(mazePtr);

    char title[] = "Binary Maze - 3D Grid";
    RendererGrid3D *rendererGridPtr = new RendererGrid3D(mazePtr, solver, title, generateCallback, solveCallback);

    int mazeSize = 5;
    //Offset the node position to make rendering easier and map to nice opengl stuff.
    int minpart = (int)floor(mazeSize/2) * -1;
    int maxpart = (int)ceil(mazeSize/2);

    std::cout << "Generating a binary maze of " << mazeSize << " by " << mazeSize << std::endl;

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

    rendererGridPtr->generate();
    rendererGridPtr->startOpenGl();

    return 0;
}
