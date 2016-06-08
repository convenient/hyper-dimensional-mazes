#include <iostream>
#include "mazebinary.h"
#include "RendererGrid2D.h"
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


int main(int argc, char **argv) {

    Maze *mazePtr = new MazeBinary;
    Solver *solver = new Solver(mazePtr);

    char title[] = "Binary Maze - 2D Grid";
    RendererGrid2D *rendererGrid2DPtr = new RendererGrid2D(mazePtr, title, render);

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

    mazePtr->generate();

    rendererGrid2DPtr->drawMaze();
    rendererGrid2DPtr->startOpenGl();

    return 0;
}
