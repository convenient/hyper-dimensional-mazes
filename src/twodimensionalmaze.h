#ifndef MAZES_FOR_PROGRAMMERS_TWODIMENSIONALMAZE_H
#define MAZES_FOR_PROGRAMMERS_TWODIMENSIONALMAZE_H

#include "twodimensionalnode.h"

#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <string>
#include <sstream>

class TwoDimensionalMaze {
private:
    std::unordered_map<std::string, TwoDimensionalNode *> map;

    std::string getMapIdentifier(int x, int y) {
        std::ostringstream stream;
        stream << x << "," << y;
        std::string result = stream.str();
        return result;
    }

public:
    TwoDimensionalMaze() {
    }

    std::unordered_map<std::string, TwoDimensionalNode *> getMap() {
        return this->map;
    }

    TwoDimensionalNode* createNode(int x, int y) {
        std::string id = this->getMapIdentifier(x, y);

        if (this->existsNode(id)) {
            throw std::logic_error("Tried to create a node where already exists");
        }

        TwoDimensionalNode *node = new TwoDimensionalNode();
        node->setX(x);
        node->setY(y);
        this->map.insert({id, node});
        return node;
    }

    void connectNodes(int x, int y, int x2, int y2) {
        TwoDimensionalNode* firstNode = getNode(x, y);
        TwoDimensionalNode* secondNode = getNode(x2, y2);

        if ((x == x2) && (abs(y-y2) == 1)) {
            if (y>y2) {
                return firstNode->setDownPtr(secondNode);
            } else {
                return firstNode->setUpPtr(secondNode);
            }
        } else if ((y == y2) && (abs(x-x2) == 1)) {
            if (x>x2) {
                return firstNode->setLeftPtr(secondNode);
            } else {
                return firstNode->setRightPtr(secondNode);
            }
        }

        throw std::logic_error("Tried to connect two non-adjacent nodes");
    }

    TwoDimensionalNode *getNode(int x, int y) {
        std::string id = this->getMapIdentifier(x, y);

        if (this->existsNode(id)) {
            return this->map.at(id);
        }
        throw std::logic_error("Tried to get a node that does not exist");
    }

    bool existsNode(std::string id) {
        if (this->map.count(id)) {
            return true;
        }
        return false;
    }
};

#endif //MAZES_FOR_PROGRAMMERS_TWODIMENSIONALMAZE_H
