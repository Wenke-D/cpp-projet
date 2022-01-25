#ifndef MOVER_H
#define MOVER_H

class Labyrinthe; // la (future) vôtre

#include "Environnement.h"
#include "FireBall.h"

const float SPEED = 0.2;


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
    /**
     * Fait tomber un personnage (gardien) et se relever
     */
    void tomber();
    /**
     * Fait tomber un personnage (gardien) et le laisse au sol.
     */
    void rester_au_sol();
    /**
     * Fait 'penser' le personnage (gardien).
     */
    virtual void update(void) = 0;

    /**
     * Fait bouger la boule de feu du personnage.
     */
    virtual bool process_fireball(float dx, float dy) = 0;

    /** 
     * Tente de déplacer le personnage de <dx,dy>.
     */
    virtual bool move(double dx, double dy) = 0;
    
    /**
     * fait tirer le personnage sur un ennemi (vous pouvez ignorer l'angle
     * vertical).
     */
    virtual void fire(int angle_vertical) = 0;

    /**
     * Appelée pour le gardien 0 (chasseur) quand l'utilisateur fait un clic
     * droit; shift (control) est vrai si la touche shift (control) est appuyée. 
     */
    virtual void right_click(bool shift, bool control) {}
};

#endif
