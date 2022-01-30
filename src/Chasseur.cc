#include "Chasseur.h"

bool Chasseur::move_aux(double dx, double dy) {

    Location l = Location((int)((_x + dx) / Environnement::scale),
                          (int)((_y + dy) / Environnement::scale));

    int v = _l->data(l.x, l.y);
    if (EMPTY == v) {
        _x += dx;
        _y += dy;
        return true;
    }
    if (bridge->reachTreasure(l)) {
        partie_terminee(true);
    }
    return false;
}

void Chasseur::updateMyPlace() {}

/**
 * Constructeur.
 */
Chasseur::Chasseur(Labyrinthe *l, Bridge *bridge, int x, int y)
    : Shooter(x * Environnement::scale, y * Environnement::scale, l, 0,
              bridge) {}

/**
 *	Clic droit: par défaut fait tomber le premier gardien.
 *
 *	Inutile dans le vrai jeu, mais c'est juste pour montrer
 *	une utilisation des fonctions "tomber" et "rester_au_sol"
 */
void Chasseur::right_click(bool shift, bool control) {
    if (shift)
        for (int i = 1; i < _l->_nguards; i++) {
            _l->_guards[i]->rester_au_sol();
        }

    else
        for (int i = 1; i < _l->_nguards; i++) {
            _l->_guards[i]->tomber();
        }
}

void Chasseur::update() {}

bool Chasseur::when_ball_moving() {
    return bridge->hitGuardien(_fb->get_x(), _fb->get_y());
}
