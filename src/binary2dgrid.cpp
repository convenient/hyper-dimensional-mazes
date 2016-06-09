#include "RendererGrid2D.h"
#include <iostream>
#include "mazebinary.h"
#include "RendererText.h"
#include "Solver.h"


void render() {

}




//void draw() {
//    rendererGrid2DPtr->drawMaze();
//    Node *startNode = getStartNode();
//    Node *endNode = getEndNode();
//
//    rendererGrid2DPtr->drawStartNode(startNode);
//    rendererGrid2DPtr->drawEndNode(endNode);
//
//    RendererText::drawNodeGoal(startNode, endNode);
//}

void generateCallback(Maze *) {
    std::cout << "Generate callback triggered " << std::endl;
}

void solveCallback(Maze *) {
    std::cout << "Solve callback triggered " << std::endl;
}

int main(int argc, char **argv) {

    Maze *mazePtr = new MazeBinary;
    Solver *solver = new Solver(mazePtr);

    char title[] = "Binary Maze - 2D Grid";
    RendererGrid2D *rendererGrid2DPtr = new RendererGrid2D(mazePtr, solver, title, generateCallback, solveCallback);

    int mazeSize = 3;
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
