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
        this->bridge->updateHunterLocation(_x, _y);
        return true;
    }
    return false;
}

void Chasseur::updateMyPlace() {}

/**
 * Constructeur.
 */
Chasseur::Chasseur(Labyrinthe *l, Bridge *bridge, int x, int y)
    : Shooter(x * Environnement::scale, y * Environnement::scale, l, 0,
              bridge) {
    // initialise les sons.
    _hunter_fire = new Sound(HUNTER_FIRE_SOUND_PATH.c_str());
    _hunter_hit = new Sound(HUNTER_HIT_SOUND_PATH.c_str());
    if (_wall_hit == 0)
        _wall_hit = new Sound(HIT_WALL_SOUND_PATH.c_str());
}

/**
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


void Chasseur::update(){

}
