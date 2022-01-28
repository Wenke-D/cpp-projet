#ifndef GARDIEN_H
#define GARDIEN_H

#include <iostream>
#include <cmath>


#include "Bridge.h"
#include "Mind.h"
#include "Mover.h"
#include "Shooter.h"

class Labyrinthe;

class Gardien : public Shooter {
  private:
    Mind mind;

    bool firing = false;

    /**
     * Try to move to case (i, j).
     *
     * @return returns true if destination is empty, false otherwise.
     *
     */
    bool try_move(int x, int y);

    /**
     * Return current location in grid level.
     */
    Location scale_down();

    /**
     * Looking for hunter in his vision
     */
    bool look_for_hunter();

    /**
     * Check if there are obstacles between hunter and the gardien
     */
    bool have_no_obstacle();

  public:
    Gardien(Labyrinthe *l, Bridge *bridge, const char *modele, int x, int y)
        : Shooter(x, y, l, modele, bridge) {}

    // mon gardien pense très mal!
    void update(void);

    // et ne bouge pas!
    bool move(double dx, double dy) { return false; };
    void after_explonation();

    void fire(int angle_vertical) override;

    void when_ball_moving() override;
};

#endif
