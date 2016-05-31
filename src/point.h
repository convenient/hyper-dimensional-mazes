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
    static const int positive = 1;
    static const int negative = -1;

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

        for (auto axisIdentifier : axis) {

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

    std::string getDifferenceDescription(Point p) {
        std::stringstream description;

        bool descriptionPopulated = false;

        for (auto axis : this->getAllAxis()) {
            int thisPosition = this->getPositionOnAxis(axis);
            int otherPosition = p.getPositionOnAxis(axis);
            int difference = abs(thisPosition - otherPosition);

            if (difference !=0) {
                if (descriptionPopulated) {
                    description << ", ";
                }
                std::string direction = "ohgodno";
                if (thisPosition < otherPosition) {
                    direction = "positive";
                } else if (thisPosition > otherPosition) {
                    direction = "negative";
                }
                description << direction << " " << difference << " on " << axis;

                descriptionPopulated = true;
            }
        }

        return description.str();
    }

    std::vector<std::string> getAllAxis(){
        //TODO object caching for this method
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
        for (auto axisIdentifier : axis) {
            basePoint.addPosition(axisIdentifier, this->getPositionOnAxis(axisIdentifier));
        }

        for (auto axisIdentifier : axis) {

            int thisPositionOnAxis = this->getPositionOnAxis(axisIdentifier);

            Point positive = this->getNeighbourPoint(basePoint, axisIdentifier, Point::positive);
            neighbouringPoints.push_back(positive);

            Point negative = this->getNeighbourPoint(basePoint, axisIdentifier, Point::negative);
            neighbouringPoints.push_back(negative);
        }

        return neighbouringPoints;
    }

    static Point getNeighbourPoint(Point origin, std::string axis, int positiveOrNegative) {
        int positionOnAxis = origin.getPositionOnAxis(axis);

        Point point = origin;
        point.unsetPosition(axis);
        point.addPosition(axis, positionOnAxis + positiveOrNegative);

        return point;
    }
};

#endif //MAZES_FOR_PROGRAMMERS_LOCATION_H
