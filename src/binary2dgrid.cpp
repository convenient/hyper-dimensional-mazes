#include <iostream>
#include "mazebinary.h"
#include "RendererGrid2D.h"
#include "RendererText.h"
MazeBinary maze;
Maze* mazePtr = &maze;
RendererGrid2D *rendererGrid2DPtr;
#include "handler.h"

void render() {

}

void processKeys(unsigned char key, int x, int y)
{
    unsigned char charKey = tolower(key);

    switch (charKey)
    {
        case 'q':
            exit(0);
            break;
        case 'g':
            generate();
            rendererGrid2DPtr->drawMaze();
            break;
        case 's': {
            std::vector<Node *> path = solve();
            rendererGrid2DPtr->drawPath(path);
            RendererText::drawPath(path);
        }
            break;
        default:
            break;
    }
}

int main(int argc, char **argv) {

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
            maze.createNode(p);
        }
    }

    maze.generate();
    char title[] = "Binary Maze - 2D Grid";

    RendererGrid2D rendererGrid2D(&maze, title, render, processKeys);
    rendererGrid2DPtr = &rendererGrid2D;

    rendererGrid2D.drawMaze();
    rendererGrid2D.startOpenGl();

    return 0;
}
