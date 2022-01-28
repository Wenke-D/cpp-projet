#pragma once

#include <map>
#include <thread>
#include <chrono>

#include "MapElement.h"
#include "Mover.h"

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
    int hunter_health = 50;
    map<Mover *, Location> gardiens;

  public:
    /**
     * Constructor
     * @param scale value of environment::scale
     */
    Bridge(int scale) : scale(scale){};
    ~Bridge();

    void updateHunterLocation(float x, float y);
    void updateGurdienLocation(Mover *shooter, float x, float y);
    bool hunterIsHit(float x, float y);
    void hitHunter();

    Location getHunterLocation() {
        return Location(hunter_x / scale, hunter_y / scale);
    };

    float get_hunter_x() { return hunter_x; };
    float get_hunter_y() { return hunter_y; };
};
