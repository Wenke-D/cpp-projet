#include "Gardien.h"

bool Gardien::try_move(int unit_x, int unit_y) {
    int x = (int)(this->_x / Environnement::scale) + unit_x;
    int y = (int)(this->_y / Environnement ::scale) + unit_y;
    if (x >= this->_l->width() || x < 0)
        return false;
    if (y >= this->_l->height() || y < 0)
        return false;
    int v = this->_l->data(x, y);
    return EMPTY == v;
}

void Gardien::update() {
    int dx, dy, angle;
    while (1) {
        angle = this->mind.think(&dx, &dy, this->_angle);
        if (this->try_move(dx, dy)) {
            break;
        }
        this->mind.rethink();
    }

    this->_x += dx * SPEED;
    this->_y += dy * SPEED;
    this->_angle = angle;
}