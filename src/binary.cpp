#include "node.h"
#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <string>
#include <sstream>

#include "opengl.h"

using namespace std;

class TwoDimensionalNode : public Node {

private:
    int x =13;
    int y = 13;

public:
    TwoDimensionalNode() {
        Axis *xAxis = new Axis('x');
        Axis *yAxis = new Axis('y');

        Dimensions dimensions;
        dimensions.addAxis(xAxis);
        dimensions.addAxis(yAxis);

        this->dimensions = dimensions;
    }

    void setX(int x) {
        this->x = x;
    }

    void setY(int y) {
        this->y = y;
    }

    int getX() {
        return this->x;
    }

    int getY() {
        return this->y;
    }
};

class TwoDimensionalMaze {
private:
    std::unordered_map<string, TwoDimensionalNode *> map;

    std::string getMapIdentifier(int x, int y) {
        std::ostringstream stream;
        stream << x << "," << y;
        std::string result = stream.str();
        return result;
    }

public:
    TwoDimensionalMaze() {
    }

    std::unordered_map<string, TwoDimensionalNode *> getMap()
    {
        return this->map;
    }

    void createNode(int x, int y) {
        string id = this->getMapIdentifier(x, y);

        if (this->existsNode(id)) {
            throw std::logic_error("Tried to create a node where already exists");
        }

        TwoDimensionalNode *node = new TwoDimensionalNode();
        node->setX(x);
        node->setY(y);
        this->map.insert({id, node});
    }

    Node* getNode(int x, int y)
    {
        string id = this->getMapIdentifier(x, y);

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

void drawSquare(int x, int y)
{
    GLfloat squareSize = 0.1;

    GLfloat xOffset = squareSize * x;
    GLfloat yOffset = squareSize * y;

    glBegin(GL_LINES);
    //Horizontal line bottom
    glVertex2f(squareSize + xOffset, yOffset);
    glVertex2f(xOffset, yOffset);

    //Vertical line left
    glVertex2f(xOffset, yOffset);
    glVertex2f(xOffset, squareSize + yOffset);

    //Horizontal line top
    glVertex2f(squareSize + xOffset, squareSize + yOffset);
    glVertex2f(xOffset, squareSize + yOffset);

    //Vertical line right
    glVertex2f(squareSize + xOffset, squareSize + yOffset);
    glVertex2f(squareSize + xOffset, yOffset);

    glEnd();
    glFlush();
}

void render() {

}

int main(int argc, char **argv) {

    opengl graphics(argc, argv, render);

    TwoDimensionalMaze maze;

    maze.createNode(0, 0);
    maze.createNode(0, 1);
    maze.createNode(1, 0);
    maze.createNode(1, 1);

    //Grey background
    glClearColor(0.75, 0.75, 0.75, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();

    for(auto i : maze.getMap())
    {
        TwoDimensionalNode* node = i.second;
        int x = node->getX();
        int y = node->getY();
        drawSquare(x, y);
    }


    graphics.startLoop();
    return 0;
}
