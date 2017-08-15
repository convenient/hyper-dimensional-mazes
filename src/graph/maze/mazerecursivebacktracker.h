#ifndef MAZES_FOR_PROGRAMMERS_MAZERECURSIVEBACKTRACKER_H
#define MAZES_FOR_PROGRAMMERS_MAZERECURSIVEBACKTRACKER_H

#include "maze.h"
#include <stack>

class MazeRecursiveBacktracker : public Maze {
public:
    std::string getName() {
        return "Recursive Backtracker";
    }

private:
    void generateAlgorithm() {

        std::stack<Node *> stack;

        Node *initialNode = this->getRandomUnvisitedNode();

        stack.push(initialNode);
        this->markNodeAsVisited(initialNode);

        while (!stack.empty()) {
            Node *node = stack.top();

            std::vector<Node *> neighbourNodes;
            for (auto neighbourNode : this->getNeighbourNodes(node)) {
                if (!this->nodeIsVisited(neighbourNode)) {
                    neighbourNodes.push_back(neighbourNode);
                }
            }

            if (neighbourNodes.empty()) {
                stack.pop();
            } else {
                unsigned long r = (unsigned long) this->getRandomNumber(0, (int) neighbourNodes.size() - 1);
                Node *chosenNode = neighbourNodes.at(r);
                this->markNodeAsVisited(chosenNode);
                this->linkNodes(node, chosenNode);
                stack.push(chosenNode);
            }
        }
    }
};

#endif //MAZES_FOR_PROGRAMMERS_MAZERECURSIVEBACKTRACKER_H
