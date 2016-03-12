#ifndef MAZES_FOR_PROGRAMMERS_DIMENSIONS_H
#define MAZES_FOR_PROGRAMMERS_DIMENSIONS_H

#include "axis.h"
#include <stdexcept>
#include <unordered_map>
#include <iostream>

class Dimensions
{
private:
    std::unordered_map<char, Axis*> dimensions;

public:
    void addAxis(Axis* axis)
    {
        char identifier = axis->getIdentifier();

        if (dimensions.count(identifier)) {
            throw std::logic_error("Axis already defined");
        }
        dimensions.insert({identifier, axis});
    }

    Axis* getAxisPtr(char identifier)
    {
        if (this->dimensions.count(identifier)) {
            return this->dimensions.at(identifier);
        } else {
            throw std::logic_error("Unexpected axis requested");
        }
    }

    Dimensions clone()
    {
        Dimensions clonedDimensions;

        for (auto iter=dimensions.begin(); iter!=dimensions.end(); ++iter) {
            Axis* axisFromIterator = (Axis*) iter->second;
            char axisIdentifier = axisFromIterator->getIdentifier();
            Axis* tempPtr = new Axis(axisIdentifier);
            clonedDimensions.addAxis(tempPtr);
        }

        return clonedDimensions;
    }
};

#endif //MAZES_FOR_PROGRAMMERS_DIMENSIONS_H
