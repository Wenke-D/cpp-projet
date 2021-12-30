#ifndef M1_CPP_PROJECT_DECORATION
#define M1_CPP_PROJECT_DECORATION

#include <string>

#include "Location.h"

using namespace std;

/**
 * Decoration is the combination of texture and location.
 */
class Decoration {
  private:
  public:
    Location l;
    string texture;
    Decoration(Location location, string texture)
        : l(location), texture(texture){};
    Decoration(int x, int y, string texture) : Decoration({x, y}, texture){};
    ~Decoration(){};
};

#endif