#include <iostream>
#include "maze/mazewilsons.h"
#include "bootstrap/RendererText.h"
#include "bootstrap/solver.h"
#include "bootstrap/RendererGrid3D.h"

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

int main(int argc, char **argv) {

    Maze *mazePtr = new MazeWilsons;
    Solver *solver = new Solver(mazePtr);

    char title[] = "Wilsons Maze - 2D Grid";
    RendererGrid3D *rendererGridPtr = new RendererGrid3D(mazePtr, solver, title, generateCallback, solveCallback);

    int mazeSize = 10;
    //Offset the node position to make rendering easier and map to nice opengl stuff.
    int minpart = (int)floor(mazeSize/2) * -1;
    int maxpart = (int)ceil(mazeSize/2);

    std::cout << "Generating a wilsons maze of " << mazeSize << " by " << mazeSize << std::endl;

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
