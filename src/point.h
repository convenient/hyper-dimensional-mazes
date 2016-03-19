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

    int getPositionOnAxis(std::string axisIdentifier) {
        if (!this->map.count(axisIdentifier)) {
            return 0;
        }

        return this->map.at(axisIdentifier);
    }

    double getEuclideanDistanceTo(Point point) {

        // d(a,b) = sqrt( (a1-b1)^2 + (a2-b2)^2 + (a3-b3)^2 + (a4-b4)^2 )

        double distance = 0;

        std::vector<std::string> axis = Point::getAllAxis(this[0], point);

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
        std::map<std::string, std::string> locDefinedAxis = b.getDefinedAxis();
        for (auto i : locDefinedAxis) {
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
};

#endif //MAZES_FOR_PROGRAMMERS_LOCATION_H
