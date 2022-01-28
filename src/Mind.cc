#include "Mind.h"

int Mind::think(int *dx, int *dy) {
    *dx = unit_x[this->direction];
    *dy = unit_y[this->direction];
    return moving_angles[this->direction];
}

void Mind::rethink() {
    this->direction += 1;
    if (this->direction >= 4) {
        this->direction = 0;
    }
}

int Mind::get_shooting_angle(){
    return shooting_angle[direction];
}