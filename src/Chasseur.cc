#include "Chasseur.h"

const string HUNTER_FIRE_SOUND_PATH = get_sound_path("hunter_fire.wav");
const string HUNTER_HIT_SOUND_PATH = get_sound_path("hunter_hit.wav");
const string HIT_WALL_SOUND_PATH = get_sound_path("hit_wall.wav");

bool Chasseur::move_aux(double dx, double dy) {

    int v = _l->data((int)((_x + dx) / Environnement::scale),
                     (int)((_y + dy) / Environnement::scale));
    if (EMPTY == v) {
        _x += dx;
        _y += dy;
        return true;
    }
    return false;
}

/**
 * Constructeur.
 */
Chasseur::Chasseur(Labyrinthe *l, int x, int y)
    : Mover(x * Environnement::scale, y * Environnement::scale, l, 0) {
    // initialise les sons.
    _hunter_fire = new Sound(HUNTER_FIRE_SOUND_PATH.c_str());
    _hunter_hit = new Sound(HUNTER_HIT_SOUND_PATH.c_str());
    if (_wall_hit == 0)
        _wall_hit = new Sound(HIT_WALL_SOUND_PATH.c_str());
}

bool Chasseur::process_fireball(float dx, float dy) {
    // calculer la distance entre le chasseur et le lieu de l'explosion.
    float x = (_x - _fb->get_x()) / Environnement::scale;
    float y = (_y - _fb->get_y()) / Environnement::scale;
    float dist2 = x * x + y * y;

    // on bouge que dans le vide!
    if (EMPTY == _l->data((int)((_fb->get_x() + dx) / Environnement::scale),
                          (int)((_fb->get_y() + dy) / Environnement::scale))) {
        message("Woooshh ..... %d", (int)dist2);
        // il y a la place.
        return true;
    }
    // collision...
    // calculer la distance maximum en ligne droite.

    float dmax2 =
        (_l->width()) * (_l->width()) + (_l->height()) * (_l->height());

    // faire exploser la boule de feu avec un bruit fonction de la distance.
    _wall_hit->play(1. - dist2 / dmax2);
    message("Booom...");
    return false;
}

/*
 *	Tire sur un ennemi.
 */

void Chasseur::fire(int angle_vertical) {
    message("Woooshh...");
    _hunter_fire->play();

    _fb->init(/* position initiale de la boule */ _x, _y, 10.,
              /* angles de visée */ angle_vertical, _angle);
}

/*
 *	Clic droit: par défaut fait tomber le premier gardien.
 *
 *	Inutile dans le vrai jeu, mais c'est juste pour montrer
 *	une utilisation des fonctions "tomber" et "rester_au_sol"
 */

void Chasseur::right_click(bool shift, bool control) {
    if (shift)
        for (size_t i = 1; i < _l->_nguards; i++) {
            _l->_guards[i]->rester_au_sol();
        }

    else
        for (size_t i = 1; i < _l->_nguards; i++) {
            _l->_guards[i]->tomber();
        }
}
