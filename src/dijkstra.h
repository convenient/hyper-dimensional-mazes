#ifndef MAZES_FOR_PROGRAMMERS_DIJKSTRA_H
#define MAZES_FOR_PROGRAMMERS_DIJKSTRA_H

#include "maze.h"

class Dijkstra {
public:
    /**
     * Returns a vector containing node pointers journeying from the start point to the end point
     * Including both the start point and the end point.
     *
     * This means the shortest path will always be 2 in size, both a start and an end.
     */
    static std::vector<Node *> getPath(Node *start, Node *end) {

        std::unordered_map<Node *, Node *> visitedNodes;

        std::vector<Node *> path;
        path.push_back(start);

        Node *workingNode = start;

        std::vector<Node *> linkedNodes = workingNode->getLinkedNodes();

        for (auto node : linkedNodes) {
            if (node == end) {
                path.push_back(node);
                break;
            }
            if (visitedNodes.at(node)) {
                //This node has already been visited
                continue;
            } else {
                visitedNodes.insert({node, node});
            }
        }

        return path;
    }
};

#endif //MAZES_FOR_PROGRAMMERS_DIJKSTRA_H
