#include "Mind.h"

int Mind::think(int *dx, int *dy, int angle) {
    *dx = unit_x[this->direction];
    *dy = unit_y[this->direction];
    return angles[this->direction];
}

void Mind::rethink() {
    this->direction += 1;
    if (this->direction >= 4) {
        this->direction = 0;
    }
}