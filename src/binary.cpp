#include "node.h"
#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <string>
#include <sstream>

#include "opengl.h"

using namespace std;

class TwoDimensionalMaze {
private:
    Dimensions dimensions;
    std::unordered_map<string, Node *> map;

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

        return this->createNode(id);
    }

    void createNode(std::string id) {
        if (this->existsNode(id)) {
            throw std::logic_error("Tried to create a node where already exists");
        }

        Node *node = new Node(dimensions.clone());
        this->map.insert({id, node});
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

    //Grey background
    glClearColor(0.75, 0.75, 0.75, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();

    drawSquare(0, 0);
    drawSquare(0, 1);
    drawSquare(1, 0);
    drawSquare(1, 1);

}

int main(int argc, char **argv) {

    opengl graphics(argc, argv, render);

    TwoDimensionalMaze maze;

    maze.createNode(0, 0);
    maze.createNode(0, 1);
    maze.createNode(1, 0);
    maze.createNode(1, 1);

    graphics.startLoop();
    return 0;
}
