#include "mazebinary.h"
#include "RendererGrid2D.h"
#include "dijkstra.h"
#include <iostream>

MazeBinary maze;
Maze* mazePtr = &maze;

void render() {

}

void solve() {
    Dijkstra dijkstraPathSolver;
    std::cout << "Solving" << std::endl;
}

void generate() {
    std::cout << "Generating" << std::endl;
    maze.generate();
}

void processKeys(unsigned char key, int x, int y)
{
    unsigned char charKey = tolower(key);

    switch (charKey)
    {
        case 'q': exit(0); break;
        case 'g': generate(); break;
        case 's': solve(); break;
        default: break;
    }
}

int main(int argc, char **argv) {

    int mazeSize = 30;
    int minpart = (int)floor(mazeSize/2) * -1;
    int maxpart = (int)ceil(mazeSize/2);

    for (int x=minpart; x<maxpart; x++) {
        for (int y=minpart; y<maxpart; y++) {
            Point p;
            p.addPosition("x", x);
            p.addPosition("y", y);
            maze.createNode(p);
        }
    }

    generate();

    char title[] = "Binary Maze - 2D Grid";

    RendererGrid2D::render(&maze, title, render, processKeys);

    return 0;
}
