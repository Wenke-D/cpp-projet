#ifndef CHASSEUR_H
#define CHASSEUR_H

#include <stdio.h>

#include "Bridge.h"
#include "Shooter.h"
#include "config.h"

class Labyrinthe;

class Chasseur : public Shooter {
  private:
    /**
     * Try to move a certain distance.
     * @param dx distance in x direction
     * @param dy distance in y direction
     * @return true if it can move, false otherwise.
     */
    bool move_aux(double dx, double dy);
    /**
     * Update to brige my newest grid place.
     */
    void updateMyPlace();

  public:

    /**
     * Constructor
     * @param l the game
     * @param x location x without scaling
     * @param y location y without scaling
     */
    Chasseur(Labyrinthe *l, Bridge *bridge, int x, int y);

    /**
     * Ne bouger que dans une case vide (on 'glisse' le long des obstacles)
     */
    bool move(double dx, double dy) {
        return move_aux(dx, dy) || move_aux(dx, 0.0) || move_aux(0.0, dy);
    }

    /**
     * le chasseur pense !
     */
    void update(){cout << "I am thinking!" << endl;};

    // clic droit.
    void right_click(bool shift, bool control);

    /**
     * Determine if the ball hit a guardien
     */
    bool when_ball_moving();
};

#endif
