#ifndef MAZES_FOR_PROGRAMMERS_LOCATION_H
#define MAZES_FOR_PROGRAMMERS_LOCATION_H

#include <string>
#include <map>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <vector>

class Location {
public:
    std::string location = "";
    std::map<std::string, int> map;
    std::map<std::string, std::string> defined_axis;

    std::map<std::string, std::string> getDefinedAxis() {
        return this->defined_axis;
    }

    void addPoint(std::string axisIdentifier, int position) {
        if (this->map.count(axisIdentifier)) {
            throw std::logic_error("Tried to add a point when axis already defined");
        }
        this->map.insert({axisIdentifier, position});
        this->defined_axis.insert({axisIdentifier, axisIdentifier});
        this->location = "";
    }

    int getPositionOnAxis(std::string axisIdentifier) {
        if (!this->map.count(axisIdentifier)) {
            return 0;
        }

        return this->map.at(axisIdentifier);
    }

    double getEuclideanDistanceTo(Location location) {

        // d(a,b) = sqrt( (a1-b1)^2 + (a2-b2)^2 + (a3-b3)^2 + (a4-b4)^2 )

        double distance = 0;

        std::vector<std::string> axis = Location::getAllAxis(this[0], location);

        for(std::vector<std::string>::reverse_iterator it = axis.rbegin(); it != axis.rend(); ++it) {
            std::string axisIdentifier = *it;

            int position = this->getPositionOnAxis(axisIdentifier);
            int comparePosition = location.getPositionOnAxis(axisIdentifier);

            distance  += pow((position - comparePosition), 2);
        }

        distance = sqrt(distance);

        return distance;
    }

    std::string getAsString() {
        if (this->location == "") {
            std::stringstream stream;

            for (auto i : this->map) {
                stream << "(" << i.first << ":" << i.second << ")";
            }

            this->location = stream.str();
        }

        return this->location;
    }

    static std::vector<std::string> getAllAxis(Location a, Location b){

        std::map<std::string, std::string> allDefinedAxis;

        //Get all the axis defined in Location a.
        for (auto i : a.getDefinedAxis()) {
            std::string axisIdentifier = i.first;
            if (!allDefinedAxis.count(axisIdentifier)) {
                allDefinedAxis.insert({axisIdentifier, axisIdentifier});
            }
        }

        //Get all the axis defined in Location b.
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
