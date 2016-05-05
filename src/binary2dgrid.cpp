#include "mazebinary.h"
#include "RendererGrid2D.h"
#include "dijkstra.h"
#include <iostream>
#include <thread>

MazeBinary maze;
Maze* mazePtr = &maze;
bool mazeSolved = false;


void render() {

}
//http://stackoverflow.com/questions/7686939/c-simple-return-value-from-stdthread
void threadtest(std::string msg)
{
    std::cout << "task1 says: " << msg;
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

    unsigned long counter = 0;
    unsigned long todo = ((deadEnds.size() * deadEnds.size())/2) - (deadEnds.size()/2);

    std::vector<Node *> longestPath;

    std::size_t num_chunks = 4;

    /**
     * Not quite All Pairs All Paths, but since A->B is the same path as B->A for shortest paths
     * This is a good approach to half the amount of paths to be calculated.
     */
    for (std::size_t i = 0; i <= deadEnds.size() + num_chunks; i+=num_chunks) {
        //CHECK IF EXISTS
        Node * start = deadEnds.at(i);
        for (std::size_t j=i+1; j<= deadEnds.size() + num_chunks; j+=num_chunks) {
            //Check if exists
            Node *end1 = deadEnds.at(j);
            Node *end2 = deadEnds.at(j);
            Node *end3 = deadEnds.at(j);
            Node *end4 = deadEnds.at(j);
//            std::vector<Node *> path = dijkstraSolver.getPath(start, end1);
//            if (path.size() > longestPath.size()) {
//                longestPath = path;
//            }

            counter++;
            if (counter % 100 ==0) {
                std::cout << counter << "/" << todo << std::endl;
            }
        }
    }

    exit(0);
//    Node *start = longestPath.front();
//    Node *end = longestPath.back();

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
