#include <iostream>
#include "mazebinary.h"
#include "RendererText.h"
MazeBinary maze;
Maze* mazePtr = &maze;
#include "handler.h"

int main(int argc, char **argv) {

    int mazeSize = 5;

    std::cout << "Generating a binary maze of " << mazeSize << " by "<< mazeSize << " by " << mazeSize << " by " << mazeSize <<  std::endl;

    for (int w=0; w< mazeSize; w++) {
        for (int x = 0; x < mazeSize; x++) {
            for (int y = 0; y < mazeSize; y++) {
                for (int z = 0; z < mazeSize; z++) {
                    Point p;
                    p.addPosition("w", w);
                    p.addPosition("x", x);
                    p.addPosition("y", y);
                    p.addPosition("z", z);
                    maze.createNode(p);
                }
            }
        }
    }
    maze.generate();

    std::vector<Node *> path = solve();
    RendererText::drawPath(path);

    return 0;
}