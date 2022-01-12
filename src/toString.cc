#include "toString.h"


std::ostream &operator<<(std::ostream &out, const Wall &w) {
    char str[128];
    sprintf(str, "(%d, %d) -> (%d, %d)", w._x1, w._y1, w._x2, w._y2);
    out << str << std::endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, const std::vector<Wall> &v) {
    for(auto& w:v){
        out << w;
    }
    return out;
}
