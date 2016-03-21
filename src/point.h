#ifndef MAZES_FOR_PROGRAMMERS_LOCATION_H
#define MAZES_FOR_PROGRAMMERS_LOCATION_H

#include <string>
#include <map>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <vector>

class Point {
private:
    std::string point = "";
    std::map<std::string, int> map;
    std::map<std::string, std::string> defined_axis;

public:
    Point() {

    }

    std::map<std::string, std::string> getDefinedAxis() {
        return this->defined_axis;
    }

    void addPosition(std::string axisIdentifier, int position) {
        if (this->map.count(axisIdentifier)) {
            throw std::logic_error("Tried to add a point when axis already defined");
        }
        this->map.insert({axisIdentifier, position});
        this->defined_axis.insert({axisIdentifier, axisIdentifier});
        this->point = "";
    }

    void unsetPosition(std::string axisIdentifier) {
        if (this->map.count(axisIdentifier)) {
            this->map.erase({axisIdentifier});
            this->defined_axis.erase({axisIdentifier});
            this->point = "";
        }
    }

    int getPositionOnAxis(std::string axisIdentifier) {
        if (!this->map.count(axisIdentifier)) {
            return 0;
        }

        return this->map.at(axisIdentifier);
    }

    double getEuclideanDistanceTo(Point point) {

        // d(a,b) = sqrt( (a1-b1)^2 + (a2-b2)^2 + (a3-b3)^2 + (a4-b4)^2 )

        double distance = 0;

        std::vector<std::string> axis = Point::getAllAxis(*this, point);

        for(std::vector<std::string>::reverse_iterator it = axis.rbegin(); it != axis.rend(); ++it) {
            std::string axisIdentifier = *it;

            int position = this->getPositionOnAxis(axisIdentifier);
            int comparePosition = point.getPositionOnAxis(axisIdentifier);

            distance  += pow((position - comparePosition), 2);
        }

        distance = sqrt(distance);

        return distance;
    }

    std::string getAsString() {
        if (this->point == "") {
            std::stringstream stream;

            for (auto i : this->map) {
                stream << "(" << i.first << ":" << i.second << ")";
            }

            this->point = stream.str();
        }

        return this->point;
    }

    std::vector<std::string> getAllAxis(){
        Point x;
        std::vector<std::string> axis = Point::getAllAxis(*this, x);
        return axis;
    }

    static std::vector<std::string> getAllAxis(Point a, Point b){

        std::map<std::string, std::string> allDefinedAxis;

        //Get all the axis defined in Point a.
        for (auto i : a.getDefinedAxis()) {
            std::string axisIdentifier = i.first;
            if (!allDefinedAxis.count(axisIdentifier)) {
                allDefinedAxis.insert({axisIdentifier, axisIdentifier});
            }
        }

        //Get all the axis defined in Point b.
        for (auto i : b.getDefinedAxis()) {
            std::string axisIdentifier = i.first;
            if (!allDefinedAxis.count(axisIdentifier)) {
                allDefinedAxis.insert({axisIdentifier, axisIdentifier});
            }
        }

        //Extract them from this temporary map and pop them in vector.
        std::vector<std::string> axis;

        for (auto i: allDefinedAxis) {
            std::string axisIdentifier = i.first;
            axis.push_back(axisIdentifier);
        }

        return axis;
    }

    std::vector<Point> getNeighbouringPoints() {

        std::vector<Point> neighbouringPoints;

        std::vector<std::string> axis = this->getAllAxis();

        //Create a base point which is cloned from the current location
        Point basePoint;
        for(std::vector<std::string>::reverse_iterator it = axis.rbegin(); it != axis.rend(); ++it) {
            std::string axisIdentifier = *it;
            basePoint.addPosition(axisIdentifier, this->getPositionOnAxis(axisIdentifier));
        }

        for(std::vector<std::string>::reverse_iterator it = axis.rbegin(); it != axis.rend(); ++it) {
            std::string axisIdentifier = *it;

            int thisPositionOnAxis = this->getPositionOnAxis(axisIdentifier);

            Point tempPositive = basePoint;
            tempPositive.unsetPosition(axisIdentifier);
            tempPositive.addPosition(axisIdentifier, thisPositionOnAxis + 1);
            neighbouringPoints.push_back(tempPositive);

            Point tempNegative = basePoint;
            tempNegative.unsetPosition(axisIdentifier);
            tempNegative.addPosition(axisIdentifier, thisPositionOnAxis - 1);
            neighbouringPoints.push_back(tempNegative);
        }

        return neighbouringPoints;
    }
};

#endif //MAZES_FOR_PROGRAMMERS_LOCATION_H
