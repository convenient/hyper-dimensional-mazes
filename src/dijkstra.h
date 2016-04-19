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
    static std::vector<Node *> getPath(Maze *maze, Point startPoint, Point endPoint) {

        if (!(maze->nodeExistsAtPoint(startPoint) && maze->nodeExistsAtPoint(endPoint))) {
            throw std::logic_error("Tried to find path between points not in maze");
        }

        std::unordered_map<std::string, Node *> unvisited = maze->getMap();

        Node *start = maze->getNodeAtPoint(startPoint);
        Node *end = maze->getNodeAtPoint(endPoint);

        std::vector<Node *> path;
        path.push_back(start);

        std::vector<Node *> neighbourNodes = maze->getNeighbourNodes(start);

        for (auto neighbourNode : neighbourNodes) {
            if (neighbourNode == end) {
                path.push_back(neighbourNode);
                break;
            }
        }

        return path;
    }
};

#endif //MAZES_FOR_PROGRAMMERS_DIJKSTRA_H
