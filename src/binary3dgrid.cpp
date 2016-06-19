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
//            for (int z=minpart; z<maxpart; z++) {
                Point p;
                p.addPosition("x", x);
                p.addPosition("y", y);
//                p.addPosition("z", z);
                mazePtr->createNode(p);
//            }
        }
    }



//    Point p;
//    p.addPosition("x", 0);
//    p.addPosition("y", -1);
//    p.addPosition("z", 0);
//    Node *n1 = mazePtr->createNode(p);
//
//    Point p2;
//    p2.addPosition("x", 0);
//    p2.addPosition("y", 0);
//    p2.addPosition("z", 0);
//    Node *n2 = mazePtr->createNode(p2);
//    n1->link(n2);

//    Point p3;
//    p3.addPosition("x", 0);
//    p3.addPosition("y", 4);
//    p3.addPosition("z", 0);
//    Node *n3 = mazePtr->createNode(p3);
//    n2->link(n3);

//    Point p4;
//    p4.addPosition("x", 0);
//    p4.addPosition("y", 5);
//    p4.addPosition("z", 0);
//    Node *n4 = mazePtr->createNode(p4);
//    n3->link(n4);

//    Point p5;
//    p5.addPosition("x", 5);
//    p5.addPosition("y", 5);
//    p5.addPosition("z", 5);
//    Node *n5 = mazePtr->createNode(p5);

    rendererGridPtr->generate();
    rendererGridPtr->startOpenGl();

    return 0;
}
