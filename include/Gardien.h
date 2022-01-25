#ifndef GARDIEN_H
#define GARDIEN_H

#include "Mover.h"
#include "Mind.h"
#include <iostream>

class Labyrinthe;

class Gardien : public Mover {
  private:
  /**
   * Try to move to case (i, j).
   * 
   * @return returns true if destination is empty, false otherwise.
   * 
   */
    bool try_move(int x, int y);
    Mind mind;
    
  public:
    Gardien(Labyrinthe *l, const char *modele, int x, int y) : Mover(x, y, l, modele) {}

    // mon gardien pense très mal!
    void update(void);

    // et ne bouge pas!
    bool move(double dx, double dy) { return false; }

    // ne sait pas tirer sur un ennemi.
    void fire(int angle_vertical) {}

    // quand a faire bouger la boule de feu...
    bool process_fireball(float dx, float dy) { return false; }
};

#endif
