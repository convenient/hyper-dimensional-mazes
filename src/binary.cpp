#include "node.h"
#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <string>
#include <sstream>

using namespace std;

class TwoDimensionalMaze {
private:
    Dimensions dimensions;
    std::unordered_map<string, Node*> map;

    std::string getMapIdentifier(int x, int y) {
        std::ostringstream stream;
        stream << x << "," << y;
        std::string result = stream.str();
        return result;
    }

public:
    TwoDimensionalMaze() {
        Axis *xAxis = new Axis('x');
        Axis *yAxis = new Axis('y');

        Dimensions dimensions;
        dimensions.addAxis(xAxis);
        dimensions.addAxis(yAxis);

        this->dimensions = dimensions;
    }

    void createNode(int x, int y) {
        string id = this->getMapIdentifier(x, y);

        if (this->existsNode(x, y)) {
            throw std::logic_error("Tried to create a node where already exists");
        }

        Node *node = new Node(dimensions.clone());
        this->map.insert({id, node});
    }

    bool existsNode(int x, int y) {
        string id = this->getMapIdentifier(x, y);
        return this->existsNode(id);
    }

    bool existsNode(std::string id) {
        if (this->map.count(id)) {
            return true;
        }
        return false;
    }
};

int main(int argc, char **argv) {

    TwoDimensionalMaze maze;

    maze.createNode(0, 0);
    maze.createNode(0, 1);
    maze.createNode(1, 0);
    maze.createNode(1, 1);

    return 0;
}
