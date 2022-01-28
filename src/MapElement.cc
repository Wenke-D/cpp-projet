#include "MapElement.h"

Location::Location(int x, int y) : x(x), y(y){};


Location Location::operator+(const Location &other) const {
    return Location(this->x + other.x, this->y + other.y);
}

Location Location::operator-(const Location &other) const {
    return Location(this->x - other.x, this->y - other.y);
}

std::ostream &operator<<(std::ostream &out, const Location &p) {
    char str[128];
    sprintf(str, "(%d, %d)", p.x, p.y);
    out << str;
    return out;
}

std::ostream &operator<<(std::ostream &out, const Picture &p) {
    out << p.start << " " << p.end << " " << p.image;
    return out;
}

Picture::Picture(int x1, int y1, int x2, int y2, std::string image)
    : Picture({x1, y1}, {x2, y2}, image) {}

Picture::Picture(Location start, Location end, std::string image)
    : start(start), end(end), image(image) {}

Picture::~Picture() {}