#ifndef MAZES_FOR_PROGRAMMERS_HANDLER_H
#define MAZES_FOR_PROGRAMMERS_HANDLER_H
#include "dijkstra.h"
#include <chrono>
#include <thread>
#include <future>
#include <iostream>

bool mazeSolved = false;

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

    int batchSize = 100;

    while (!batches.empty()) {

        std::vector<std::future<std::vector<Node *>>> futuresSolutions;
        int counter = 0;

        std::vector<Node *> batchesToRemove;

        for (auto batch : batches) {
            Node * start = batch.first;
            std::vector<Node *> endPoints = batch.second;

            batchesToRemove.push_back(start);
            futuresSolutions.push_back(std::async(std::launch::async, &getLongestPath, start, endPoints));

            if (counter++ == batchSize) {
                break;
            }
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

std::vector<Node *> solve() {
    std::vector<Node *> longestPath;

    if (mazeSolved) {
        return longestPath;
    }
    std::vector<Node *> deadEnds = maze.getDeadEnds();
    if (deadEnds.size() < 2) {
        std::cout << "Er....not enough dead ends to solve" << std::endl;
        return longestPath;
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

    longestPath = getLongestPathFromBatches(batches);
    batches.clear();

    mazeSolved = true;

    auto current_time = std::chrono::high_resolution_clock::now();
    std::cout << "Solution took " << std::chrono::duration_cast<std::chrono::duration<float>>(current_time - start_time).count() << " seconds and has a distance of " << longestPath.size() << std::endl;

    return longestPath;
}

void generate() {
    std::cout << "Generating" << std::endl;
    maze.generate();
    mazeSolved = false;
}

#endif //MAZES_FOR_PROGRAMMERS_HANDLER_H
