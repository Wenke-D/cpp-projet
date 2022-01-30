#include "Gardien.h"

/**
 * return atan(b/a) in degree rep
 */
int angle_of_points(float b, float a) { return atan(b / a) * 180 / M_PI; }

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
    // Behaviors when gardien is in peace
    if (mind.state == State::peace) {
        // update movement
        int dx, dy, angle;
        while (1) {
            angle = this->mind.think(&dx, &dy);
            if (this->try_move(dx, dy)) {
                break;
            }
            this->mind.rethink();
        }
        this->_x += dx * SPEED;
        this->_y += dy * SPEED;
        this->_angle = angle;
    }
    // Behaviors when gardien is in fight state
    else if (mind.state == State::fight) {
        if (!firing) {
            fire(360);
            firing = true;
        }
    }
    /* Behavior of dead */
    else{
        return;
    }

    /* Behaviors no matter in what state */
    // looking for hunter to update state
    bool rightDirection = look_for_hunter();
    bool noObstacle = have_no_obstacle();
    if (rightDirection && noObstacle) {
        this->mind.state = State::fight;
    } else {
        this->mind.state = State::peace;
    }
}

Location Gardien::scale_down() {
    int x = int(this->_x / Environnement::scale);
    int y = int(this->_y / Environnement::scale);
    return Location(x, y);
}

/**
 * Check if the gardien is face to hunter.
 * @param dir the integer indicating gardien's face direction
 * @param diff the difference between the hunter and the gardien (not reverse)
 */
bool check_direction(int dir, Location diff) {
    switch (dir) {
    case 0:
        return diff.y > 0;

    case 1:
        return diff.x < 0;

    case 2:
        return diff.y < 0;

    case 3:
        return diff.x > 0;

    default:
        cerr << "Direction go wrong" << endl;
        exit(2);
    }
}

bool Gardien::look_for_hunter() {
    Location hunter = this->bridge->getHunterLocation();
    Location me = this->scale_down();

    Location diff = hunter - me;

    if (!check_direction(this->mind.direction, diff)) {
        return false;
    }
    return true;
}

bool Gardien::have_no_obstacle() {
    size_t begin_x = min(bridge->getHunterLocation().x, scale_down().x),
           begin_y = min(bridge->getHunterLocation().y, scale_down().y),
           end_x = max(bridge->getHunterLocation().x, scale_down().x),
           end_y = max(bridge->getHunterLocation().y, scale_down().y);
    for (size_t x = begin_x; x < end_x; x++) {
        for (size_t y = begin_y; y < end_y; y++) {
            if (_l->data(x, y) == FILL) {
                return false;
            }
        }
    }
    return true;
}

void Gardien::after_explonation() { firing = false; }

/**
 * fait tirer le personnage sur un ennemi (vous pouvez ignorer l'angle
 * vertical).
 */
void Gardien::fire(int angle_vertical) {
    message("Woooshh...");
    // _hunter_fire->play();

    /* fix shooting angle,
     * somehow shoting angle and moving angle are diff in folling two angle
     */
    int fire_angle = _angle;
    if (fire_angle == 270)
        fire_angle = 90;
    else if (fire_angle == 90)
        fire_angle = 270;

    int diff = 0, final_angle = 0;
    if (fire_angle == 270 || fire_angle == 90) {
        diff = angle_of_points(bridge->get_hunter_y() - _y,
                               bridge->get_hunter_x() - _x);
        final_angle = fire_angle - diff;
    } else {
        diff = angle_of_points(bridge->get_hunter_x() - _x,
                               bridge->get_hunter_y() - _y);
        final_angle = fire_angle + diff;
    }

    printf("face angle: %d, diff: %d\n", fire_angle, diff);
    _fb->init(_x, _y, 10., 360, final_angle);
}

bool Gardien::when_ball_moving() {
    bool isHit = bridge->hunterIsHit(_fb->get_x(), _fb->get_y());
    if (isHit) {
        bridge->hitHunter();
    }
    return isHit;
}

void Gardien::whenDead() { this->rester_au_sol(); this->mind.state = State::dead; };
