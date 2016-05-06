#include "mazebinary.h"
#include "RendererGrid2D.h"
#include "dijkstra.h"
#include <iostream>
#include <thread>

#include <future>

void simplefunc(Node *start, Node *end)
{
    if (end == nullptr) {
        return;
    }
    std::cout << "calculating " << std::endl;

    Dijkstra dijkstraSolver;
    std::vector<Node *> path = dijkstraSolver.getPath(start, end);


//    return path;
}

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

    unsigned long counter = 0;
    unsigned long todo = ((deadEnds.size() * deadEnds.size())/2) - (deadEnds.size()/2);

    std::vector<Node *> longestPath;

    std::size_t num_chunks = 2;

    /**
     * Not quite All Pairs All Paths, but since A->B is the same path as B->A for shortest paths
     * This is a good approach to half the amount of paths to be calculated.
     */
    for (std::size_t i = 0; i <= deadEnds.size(); i+=num_chunks) {
        //CHECK IF EXISTS
        if (i > deadEnds.size()) {
            break;
        }
        Node *start = deadEnds.at(i);
        for (std::size_t j=i+1; j<= deadEnds.size() + num_chunks; j+=num_chunks) {
            //Check if exists
            Node *end1 = nullptr;
            Node *end2 = nullptr;

            if (j <= deadEnds.size()) {
                end1 = deadEnds.at(j);
            }
            if (j+1 <= deadEnds.size()) {
                end2 = deadEnds.at(j+1);
            }

            std::thread t1(simplefunc(start, end1)), t2(simplefunc(start, end2));

            t1.join();
            t2.join();

//
//            auto future1 = std::async(simplefunc, start, end1);
//            auto future2 = std::async(simplefunc, start, end2);
//
//            std::vector<Node *> path1 = future1.get();
//            std::vector<Node *> path2 = future2.get();
//
//            if (path1.size() > path2.size() && path1.size() > longestPath.size()) {
//                longestPath = path1;
//            } else if (path2.size() > path1.size() && path2.size() > longestPath.size()) {
//                longestPath = path1;
//            }

            counter++;
//            if (counter % 100 ==0) {
                std::cout << counter << "/" << todo << std::endl;
//            }
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
