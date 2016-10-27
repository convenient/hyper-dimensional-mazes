#ifndef MAZES_FOR_PROGRAMMERS_MAZEALDOUSBRODER_H
#define MAZES_FOR_PROGRAMMERS_MAZEALDOUSBRODER_H

#include "maze.h"

class MazeAldousBroder : public Maze {
public:
    std::string getName() {
        return "Aldous Broder";
    }

private:
    void generateAlgorithm() {

        std::vector<std::string> axis = this->getAllAxis();

        Node *workingNode = this->getRandomUnvisitedNode();

        while (this->getUnvisitedNodeCount() > 0) {
            Point workingPoint = workingNode->getPoint();

            std::vector<Node *> neighbourNodes = this->getNeighbourNodes(workingNode);
            unsigned long r = (unsigned long) this->getRandomNumber(0, (int) neighbourNodes.size() - 1);
            Node *chosenNode = neighbourNodes.at(r);

            if (!this->nodeIsVisited(chosenNode)) {
                this->linkNodes(workingNode, chosenNode);
            }
            if (!this->nodeIsVisited(workingNode)) {
                this->markNodeAsVisited(workingNode);
            }
            workingNode = chosenNode;
        }
    }
};

#endif //MAZES_FOR_PROGRAMMERS_MAZEALDOUSBRODER_H
