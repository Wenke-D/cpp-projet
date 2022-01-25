

enum class State { peace, fight };

const int angles[4] = {0, 90, 180, 270};
const int unit_x[4] = {0, -1, 0, 1};
const int unit_y[4] = {1, 0, -1, 0};

class Mind {
  private:
    State state;
    int direction;

  public:
    Mind() : state(State::peace), direction(0) {}
    int think(int *dx, int *dy, int angle);
    void rethink();
};