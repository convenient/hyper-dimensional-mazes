#ifndef MAZES_FOR_PROGRAMMERS_AXIS_H
#define MAZES_FOR_PROGRAMMERS_AXIS_H

#include <stdexcept>

class Axis
{
public:

    static const int negative = 0;
    static const int positive = 1;

    void* positivePtr = nullptr;
    void* negativePtr = nullptr;

    void* getPtr(int direction)
    {
        if (direction == Axis::positive) {
            return this->getPositivePtr();
        } else if (direction == Axis::negative) {
            return this->getNegativePtr();
        } else {
            throw std::logic_error("Unexpected axis direction given");
        }
    }

    void* getPositivePtr()
    {
        return this->positivePtr;
    }

    void* getNegativePtr()
    {
        return this->negativePtr;
    }

    void setPtr(int direction, void* ptr)
    {
        if (direction == Axis::positive) {
            return this->setPositivePtr(ptr);
        } else if (direction == Axis::negative) {
            return this->setNegativePtr(ptr);
        } else {
            throw std::logic_error("Unexpected axis direction given");
        }
    }

    void setPositivePtr(void* ptr)
    {
        this->positivePtr = ptr;
    }

    void setNegativePtr(void* ptr)
    {
        this->negativePtr = ptr;
    }

    static int getOppositeDirection(int direction) {
        if (direction == Axis::positive) {
            return Axis::negative;
        } else if (direction == Axis::negative) {
            return Axis::positive;
        } else {
            throw std::logic_error("Unexpected axis direction given");
        }
    }};

#endif //MAZES_FOR_PROGRAMMERS_AXIS_H
