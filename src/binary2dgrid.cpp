#include <iostream>
#include <chrono>
#include <iostream>
#include <thread>
#include <future>
#include "mazebinary.h"
#include "RendererGrid2D.h"
#include "dijkstra.h"

MazeBinary maze;
Maze* mazePtr = &maze;
bool mazeSolved = false;


void render() {

}

std::vector<Node *> getLongestPath(Node *start, std::vector<Node *> endPoints) {
    Dijkstra dijkstraSolver;

    std::vector<Node *> longestPath;

    std::unordered_map<Node *, std::vector<Node *>> potentialSolvedPaths =
            dijkstraSolver.getPath(start, endPoints);
    for (auto potentialSolvedPath : potentialSolvedPaths) {
        std::vector<Node *> potentialPath = potentialSolvedPath.second;
        if (potentialPath.size() > longestPath.size()) {
            longestPath = potentialPath;
        }
    }

    return longestPath;
}

std::vector<Node *> getLongestPathFromBatches(std::unordered_map<Node *, std::vector<Node *>> batches) {
    std::vector<Node *> longestPath;

    int batchSize = 40;

    while (!batches.empty()) {

        std::vector<std::future<std::vector<Node *>>> futuresSolutions;
        int counter = 0;

        std::vector<Node *> batchesToRemove;

        for (auto batch : batches) {
            Node * start = batch.first;
            std::vector<Node *> endPoints = batch.second;

            batchesToRemove.push_back(start);
            futuresSolutions.push_back(std::async(&getLongestPath, start, endPoints));
        }

        for (std::size_t i = 0; i != futuresSolutions.size(); ++i) {
            std::vector<Node *> potentialLongestPath = futuresSolutions[i].get();
            if (potentialLongestPath.size() > longestPath.size()) {
                longestPath = potentialLongestPath;
            }
        }

        for (auto batchToRemove : batchesToRemove) {
            batches.erase(batchToRemove);
        }
    }

    return longestPath;
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

    auto start_time = std::chrono::high_resolution_clock::now();

    std::unordered_map<Node *, std::vector<Node *>> batches;

    /**
     * Not quite All Pairs All Paths, but since A->B is the same path as B->A for shortest paths
     * This is a good approach to half the amount of paths to be calculated.
     *
     * Split them into batches of start node -> many end nodes
     */
    for (std::size_t i = 0; i < deadEnds.size(); i++) {
        Node * start = deadEnds.at(i);
        std::vector<Node *> endPoints;
        for (std::size_t j=i+1; j< deadEnds.size(); j++) {
            Node *end = deadEnds.at(j);
            endPoints.push_back(end);
        }
        batches.insert({start, endPoints});
    }

    std::vector<Node *> longestPath = getLongestPathFromBatches(batches);
    batches.clear();

    RendererGrid2D::drawPath(mazePtr, longestPath);
    mazeSolved = true;

    auto current_time = std::chrono::high_resolution_clock::now();
    std::cout << "Solution took " << std::chrono::duration_cast<std::chrono::duration<float>>(current_time - start_time).count() << " seconds and has a distance of " << longestPath.size() << std::endl;

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

    int mazeSize = 25;
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
