#pragma once
#include "MapElement.h"
/**
 * Communication bridge to transfer data among the hunter and all guardiens.
 *
 *
 */
class Bridge {
  private:
    /**
     * The value of environment::scale
     */
    int scale;
    float hunter_x;
    float hunter_y;

  public:
    /**
     * Constructor
     * @param scale value of environment::scale
     */
    Bridge(int scale) : scale(scale){};
    ~Bridge();

    void updateHunterLocation(float x, float y);

    Location getHunterLocation() {
        return Location(hunter_x / scale, hunter_y / scale);
    };

    float get_hunter_x() { return hunter_x; };
    float get_hunter_y() { return hunter_y; };
};
