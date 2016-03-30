#include "mazebinary.h"
#include "RendererGrid2D.h"

using namespace std;

void render() {

}

int main(int argc, char **argv) {

    MazeBinary maze;

    int mazeSize = 12;
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

    maze.generate();

    char title[] = "Binary Maze - 2D Grid";

    RendererGrid2D::render(&maze, title, render);

    return 0;
}
