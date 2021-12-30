#include "Picture.h"

Picture::Picture(int x1, int y1, int x2, int y2, std::string image)
    : Picture({x1, y1}, {x2, y2}, image) {}

Picture::Picture(Location start, Location end, std::string image)
    : start(start), end(end), image(image) {}

Picture

    ::~Picture() {}