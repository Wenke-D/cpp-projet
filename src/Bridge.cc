#include "Bridge.h"

void Bridge::updateHunterLocation(float x, float y) {
    this->hunter_x = x;
    this->hunter_y = y;
};

void Bridge::updateGurdienLocation(Mover *shooter, float x, float y){};
bool Bridge::hunterIsHit(float x, float y) {

    int h_x = this->hunter_x / scale;
    int h_y = this->hunter_y / scale;
    int b_x = x / scale;
    int b_y = y / scale;

    return h_x == b_x && h_y == b_y;
};

void Bridge::hitHunter() {
    hunter_health -=5 ;
    printf("Hunter health: %d\n", hunter_health);
    message("Hunter health: %d\n", hunter_health);
    if (hunter_health <= 0) {
        cout << "You lose !" << endl;
        partie_terminee(false);
    }
};