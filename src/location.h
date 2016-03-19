#ifndef MAZES_FOR_PROGRAMMERS_LOCATION_H
#define MAZES_FOR_PROGRAMMERS_LOCATION_H

#include <string>
#include <map>
#include <sstream>
#include <stdexcept>

class Location {
private:
    std::map<std::string, int> map;
    std::string location = "";

public:
    void addPoint(std::string identifier, int position) {
        if (this->map.count(identifier)) {
            throw std::logic_error("Tried add identifier where already exists");
        }
        this->map.insert({identifier, position});
        this->location = "";
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
};

#endif //MAZES_FOR_PROGRAMMERS_LOCATION_H
