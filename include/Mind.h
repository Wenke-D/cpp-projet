

enum class State { peace, fight, dead };

const int shooting_angle[4] = {0, 270, 180, 90};
const int moving_angles[4] = {0, 90, 180, 270};
const int unit_x[4] = {0, -1, 0, 1};
const int unit_y[4] = {1, 0, -1, 0};

struct Mind {
    State state;
    int direction;

    Mind() : state(State::peace), direction(0) {}

    /**
     * Think instruction for next step.
     * dx and dy only will have following value (0, 1), (-1, 0), (0, -1) and (1,
     * 0) to indicate moving direction.
     *
     * @param dx a return value in parameter
     * @param dy a return value in parameter
     * @return face angle for this instruction.
     */
    int think(int *dx, int *dy);

    /**
     * Make mind to change moving direction.
     *
     */
    void rethink();

    int get_shooting_angle();
};