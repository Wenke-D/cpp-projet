#include "Bridge.h"

bool Bridge::hunterIsHit(float x, float y) {

    int h_x = this->hunter->_x / scale;
    int h_y = this->hunter->_y / scale;
    int b_x = x / scale;
    int b_y = y / scale;

    return h_x == b_x && h_y == b_y;
};

void Bridge::hitHunter() {
    bool dead = hunter->receiveDamage(5);
    printf("Hunter health: %d\n", hunter->get_health());
    message("Hunter health: %d\n", hunter->get_health());
    if (dead) {
        cout << "You lose !" << endl;
        partie_terminee(false);
    }
};

bool Bridge::hitGuardien(float x, float y) {
    int b_x = x / scale;
    int b_y = y / scale;

    for (auto g : this->gardiens) {
        int g_x = g->_x / scale;
        int g_y = g->_y / scale;

        if (b_x == g_x && b_y == g_y) {
            g->tomber();
            g->receiveDamage(5);
            cout << "Hit a gurdien, health left: " << g->get_health() << endl;
            return true;
        }
    }
    return false;
}
