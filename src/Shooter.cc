#include "Shooter.h"

/**
 * Fait bouger la boule de feu du personnage.
 */
bool Shooter::process_fireball(float dx, float dy) {
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

    // float dmax2 =
    //     (_l->width()) * (_l->width()) + (_l->height()) * (_l->height());

    // faire exploser la boule de feu avec un bruit fonction de la distance.
    // _wall_hit->play(1. - dist2 / dmax2);
    message("Booom...");
    after_explonation();
    return false;
}

/**
 * fait tirer le personnage sur un ennemi (vous pouvez ignorer l'angle
 * vertical).
 */
void Shooter::fire(int angle_vertical) {
    message("Woooshh...");
    // _hunter_fire->play();
    printf("Init a ball vertical angle: %d, horizontal angle: %d\n", angle_vertical, _angle);
    _fb->init(_x, _y, 10., angle_vertical, _angle);
}