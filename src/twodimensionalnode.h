#ifndef MAZES_FOR_PROGRAMMERS_TWODIMENSIONALNODE_H
#define MAZES_FOR_PROGRAMMERS_TWODIMENSIONALNODE_H

#include "node.h"

class TwoDimensionalNode : public Node {

private:
    int x;
    int y;

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


#endif //MAZES_FOR_PROGRAMMERS_TWODIMENSIONALNODE_H
