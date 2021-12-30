#include "Location.h"
#include <string>

class Picture {
  private:
    /* data */
  public:
    Location start;
    Location end;
    std::string image;

    Picture(Location start, Location end, std::string image);
    Picture(int x1, int y1, int x2, int y2, std::string image);

    ~Picture();
};

