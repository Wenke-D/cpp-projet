#ifndef MOVER_H
#define MOVER_H

class Labyrinthe; // la (future) vôtre

#include "Environnement.h"
#include "FireBall.h"

class Mover {
  private:
    // initialise le modêle md2.
    static void *init(const char *);

  public:
    /* le labyrinthe dans lequel il évolue. */
    Environnement *_l;
    // sa boule de feu.
    FireBall *_fb;
    // position.
    float _x, _y;
    // angle de déplacement/tir.
    int _angle;
    // le modêle graphique.
    void *_model;

    Mover(int x, int y, Labyrinthe *l, const char *modele)
        : _l((Environnement *)l), _fb(0), _x((float)x), _y((float)y),
          _angle(0) {
        _model = init(modele);
    }
    virtual ~Mover() {}
    void tomber(); // fait tomber un personnage (gardien) et se relever
    void
    rester_au_sol(); // fait tomber un personnage (gardien) et le laisse au sol.
    virtual void update(void) = 0; // fait 'penser' le personnage (gardien).
    // fait bouger la boule de feu du personnage.
    virtual bool process_fireball(float dx, float dy) = 0;
    // tente de déplacer le personnage de <dx,dy>.
    virtual bool move(double dx, double dy) = 0;
    // fait tirer le personnage sur un ennemi (vous pouvez ignorer l'angle
    // vertical).
    virtual void fire(int angle_vertical) = 0;
    // appelée pour le gardien 0 (chasseur) quand l'utilisateur fait un clic
    // droit; shift (control) est vrai si la touche shift (control) est appuy�e.
    virtual void right_click(bool shift, bool control) {}
};

#endif
