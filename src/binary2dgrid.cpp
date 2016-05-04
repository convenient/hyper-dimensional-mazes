#include "mazebinary.h"
#include "RendererGrid2D.h"
#include "dijkstra.h"
#include <iostream>
#include <sstream>

MazeBinary maze;
Maze* mazePtr = &maze;
bool mazeSolved = false;


void render() {

}

void solve() {
    if (mazeSolved) {
        return;
    }
    std::vector<Node *> deadEnds = maze.getDeadEnds();
    if (deadEnds.size() < 2) {
        std::cout << "Er....not enough dead ends to solve" << std::endl;
        return;
    }
    std::cout << "Solving" << std::endl;
    Dijkstra dijkstraSolver;

    std::unordered_map<std::string, std::string> solvedPath;

    int counter = 0;
    int complexityMaxSize = deadEnds.size() * deadEnds.size();
    std::vector<Node *> longestPath;
    //TODO replace this with a method of addressing the children by id location from within the vecotr to reduce the cost of the loops.
    for (auto deadEndNodeStart : deadEnds) {
        for (auto deadEndNodeEnd : deadEnds) {
            if (counter % 100 == 0) {

                std::cout << counter++ << "/" << complexityMaxSize << std::endl;
            }

            std::stringstream ss1;
            ss1 << deadEndNodeStart->getPoint().getAsString() << deadEndNodeEnd->getPoint().getAsString();
            std::string id1 = ss1.str();

            std::stringstream ss2;
            ss2 << deadEndNodeEnd->getPoint().getAsString() << deadEndNodeStart->getPoint().getAsString();
            std::string id2 = ss2.str();

            if (solvedPath.count(id1) || solvedPath.count(id2)) {
                continue;
            }

            //TODO keep track of node parings solved, so that we don't keep repeating the same path again and again.
            if (deadEndNodeEnd == deadEndNodeStart) {
                continue;
            }
            std::vector<Node *> path = dijkstraSolver.getPath(deadEndNodeStart, deadEndNodeEnd);
            if (path.size() > longestPath.size()) {
                longestPath = path;
            }

            solvedPath.insert({id1, id1});
            solvedPath.insert({id2, id2});
        }
    }
    Node *start = longestPath.front();
    Node *end = longestPath.back();

    std::cout << longestPath.size() << std::endl;
    RendererGrid2D::drawPath(mazePtr, longestPath);
    mazeSolved = true;
}

void generate() {
    std::cout << "Generating" << std::endl;
    maze.generate();
    RendererGrid2D::drawMaze(mazePtr);
    mazeSolved = false;
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

    std::cout << "Generating a binary maze of " << maxpart << " by " << maxpart << std::endl;

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
    RendererGrid2D::init(&maze, title, render, processKeys);

    return 0;
}
