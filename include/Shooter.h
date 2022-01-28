#pragma once
#include "Bridge.h"
#include "Mover.h"
class Shooter : public Mover {
  public:
    Bridge *bridge;

    Shooter(int x, int y, Labyrinthe *l, const char *modele, Bridge *bridge)
        : Mover(x, y, l, modele), bridge(bridge){};

    /**
     * Fait bouger la boule de feu.
     * @param dx avancement in x direction
     * @param dy advance in y direction
     * @return Return true if it can move, false otherwise
     */
    bool process_fireball(float dx, float dy) override;

    /**
     * fait tirer le personnage sur un ennemi (vous pouvez ignorer l'angle
     * vertical).
     */
    virtual void fire(int angle_vertical) override;

    virtual void after_explonation(){};
};