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

    unsigned long counter = 0;
    unsigned long todo = ((deadEnds.size() * deadEnds.size())/2) - (deadEnds.size()/2);

    std::vector<Node *> longestPath;

    /**
     * Not quite All Pairs All Paths, but since A->B is the same path as B->A for shortest paths
     * This is a good approach to half the amount of paths to be calculated.
     */
    for (std::size_t i = 0; i < deadEnds.size(); ++i) {
        Node * start = deadEnds.at(i);
        std::vector<Node *> endPoints;
        for (std::size_t j=i+1; j< deadEnds.size(); ++j) {
            Node *end = deadEnds.at(j);
            endPoints.push_back(end);
        }

        std::unordered_map<Node *, std::vector<Node *>> potentialSolvedPaths = dijkstraSolver.getPath(start, endPoints);
        for (auto potentialSolvedPath : potentialSolvedPaths) {
            std::cout << counter++ << "/" << todo << std::endl;
            std::vector<Node *> potentialPath = potentialSolvedPath.second;
            if (potentialPath.size() > longestPath.size()) {
                longestPath = potentialPath;
            }
        }

        std::cout << counter++ << "/" << todo << std::endl;
    }

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
