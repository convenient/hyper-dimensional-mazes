#include <iostream>
#include "mazebinary.h"
#include "RendererText.h"
#include "Solver.h"
#include "RendererGrid2D.h"

void generateCallback(Maze *m, Solver *s) {
    RendererText::drawNodeGoal(s->getStartNode(), s->getEndNode());
}

void solveCallback(Maze *m, Solver *s) {
    RendererText::drawPath(s->solve());
}

int main(int argc, char **argv) {

    Maze *mazePtr = new MazeBinary;
    Solver *solver = new Solver(mazePtr);

    char title[] = "Binary Maze - 2D Grid";
    RendererGrid2D *rendererGrid2DPtr = new RendererGrid2D(mazePtr, solver, title, generateCallback, solveCallback);

    int mazeSize = 30;
    //Offset the node position to make rendering easier and map to nice opengl stuff.
    int minpart = (int)floor(mazeSize/2) * -1;
    int maxpart = (int)ceil(mazeSize/2);

    std::cout << "Generating a binary maze of " << mazeSize << " by " << mazeSize << std::endl;

    for (int x=minpart; x<maxpart; x++) {
        for (int y=minpart; y<maxpart; y++) {
            Point p;
            p.addPosition("x", x);
            p.addPosition("y", y);
            mazePtr->createNode(p);
        }
    }

    rendererGrid2DPtr->generate();
    rendererGrid2DPtr->startOpenGl();

    return 0;
}
