#pragma once

#include <chrono>
#include <thread>
#include <vector>

#include "MapElement.h"
#include "Shooter.h"

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
    Shooter *hunter;
    vector<Shooter *> gardiens;

    Location treasure;

  public:
    /**
     * Constructor
     * @param scale value of environment::scale
     */
    Bridge(int scale,Location treasure) : scale(scale),treasure(treasure){};
    ~Bridge();

    inline void registreHunter(Shooter *hunter) { this->hunter = hunter; };
    inline void registreGardien(Shooter *gardien) {
        gardiens.push_back(gardien);
    };

    /**
     * Check if the ball shoot by gurdiens hit the hunter
     * @param x x coordinate of the ball's location
     * @param y y coordinate of the ball's location
     */
    bool hunterIsHit(float x, float y);

    /**
     * Detech if the ball hit a guardien, if hit, decrease correspond guardien's
     * health.
     */
    bool hitGuardien(float x, float y);

    /**
     * Data update when the ball has hit the hunter
     */
    void hitHunter();

    Location getHunterLocation() {
        return Location(hunter->_x / scale, hunter->_y / scale);
    };

    float get_hunter_x() { return hunter->_x; };
    float get_hunter_y() { return hunter->_y; };

    inline bool reachTreasure(const Location& l){return treasure == l;}
};
