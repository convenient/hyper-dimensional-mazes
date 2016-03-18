#ifndef MAZES_FOR_PROGRAMMERS_TWODIMENSIONALNODE_H
#define MAZES_FOR_PROGRAMMERS_TWODIMENSIONALNODE_H

#include "node.h"

class TwoDimensionalNode : public Node {

const char X_AXIS = 'x';
const char Y_AXIS = 'y';

private:
    int x;
    int y;

public:
    TwoDimensionalNode() {
        Axis *xAxis = new Axis(this->X_AXIS);
        Axis *yAxis = new Axis(this->Y_AXIS);

        Dimensions dimensions;
        dimensions.addAxis(xAxis);
        dimensions.addAxis(yAxis);

        this->dimensions = dimensions;
    }

    TwoDimensionalNode* getRightPtr() {
        return (TwoDimensionalNode*) this->getPtr(this->X_AXIS, Axis::positive);
    }

    TwoDimensionalNode* getLeftPtr() {
        return (TwoDimensionalNode*) this->getPtr(this->X_AXIS, Axis::negative);
    }

    TwoDimensionalNode* getUpPtr() {
        Node *n = this->getPtr(this->Y_AXIS, Axis::positive);
        if (n == nullptr) {
            return nullptr;
        }
        //Todo refactor out with generics or templates or w/e theyre caled in c++
        return (TwoDimensionalNode*) n;
    }

    TwoDimensionalNode* getDownPtr() {
        Node *n = this->getPtr(this->Y_AXIS, Axis::negative);
        if (n == nullptr) {
            return nullptr;
        }
        //Todo refactor out with generics or templates or w/e theyre caled in c++
        return (TwoDimensionalNode*) n;
    }

    void setRightPtr(TwoDimensionalNode *node) {
        this->setPtr(this->X_AXIS, Axis::positive, node);
    }

    void setLeftPtr(TwoDimensionalNode *node) {
        this->setPtr(this->X_AXIS, Axis::negative, node);
    }

    void setUpPtr(TwoDimensionalNode *node) {
        this->setPtr(this->Y_AXIS, Axis::positive, node);
    }

    void setDownPtr(TwoDimensionalNode *node) {
        this->setPtr(this->Y_AXIS, Axis::negative, node);
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
