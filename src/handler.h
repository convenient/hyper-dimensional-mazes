#ifndef MAZES_FOR_PROGRAMMERS_HANDLER_H
#define MAZES_FOR_PROGRAMMERS_HANDLER_H
#include "dijkstra.h"







void generate() {
    std::cout << "Generating" << std::endl;
    maze.generate();
    solvedPath = solve();
    mazeSolved = false;
}

Node *getStartNode() {
    return solvedPath.front();
}

Node *getEndNode() {
    return solvedPath.back();
}

std::vector<Node *> getSolvedPath() {
    return solvedPath;
}

#endif //MAZES_FOR_PROGRAMMERS_HANDLER_H
