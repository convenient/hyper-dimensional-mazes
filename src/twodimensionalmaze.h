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

    void createNode(int x, int y) {
        std::string id = this->getMapIdentifier(x, y);

        if (this->existsNode(id)) {
            throw std::logic_error("Tried to create a node where already exists");
        }

        TwoDimensionalNode *node = new TwoDimensionalNode();
        node->setX(x);
        node->setY(y);
        this->map.insert({id, node});
    }

    Node *getNode(int x, int y) {
        std::string id = this->getMapIdentifier(x, y);

        if (this->existsNode(id)) {
            this->map.at(id);
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
