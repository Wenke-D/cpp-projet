#pragma once
#include "Mover.h"
#include "Sound.h"
#include "config.h"

class Bridge;

const string HUNTER_FIRE_SOUND_PATH = get_sound_path("hunter_fire.wav");
const string HUNTER_HIT_SOUND_PATH = get_sound_path("hunter_hit.wav");
const string HIT_WALL_SOUND_PATH = get_sound_path("hit_wall.wav");

/**
 * Shooter is a mover that can shoot and get hit
 */
class Shooter : public Mover {

  protected:
    int health;

  public:
    // les sons.
    static Sound *_hunter_fire; // bruit de l'arme du chasseur.
    static Sound *_hunter_hit;  // cri du chasseur touché.
    static Sound *_wall_hit;    // on a tapé un mur.

    Bridge *bridge;

  public:
    Shooter(int health, int x, int y, Labyrinthe *l, const char *modele,
            Bridge *bridge)
        : Mover(x, y, l, modele), health(health), bridge(bridge) {
        _hunter_fire = new Sound(HUNTER_FIRE_SOUND_PATH.c_str());
        _hunter_hit = new Sound(HUNTER_HIT_SOUND_PATH.c_str());
        _wall_hit = new Sound(HIT_WALL_SOUND_PATH.c_str());
    };

    /**
     * Fait bouger la boule de feu.
     * @param dx avancement in x direction
     * @param dy advance in y direction
     * @return Return true if it can move, false otherwise
     */
    bool process_fireball(float dx, float dy) override;

    /**
     * Fait tirer le personnage sur un ennemi (vous pouvez ignorer l'angle
     * vertical).
     */
    virtual void fire(int angle_vertical) override;

    /**
     * Event to be triggerred after the ball exploded.
     */
    virtual void after_explonation() {}

    /**
     * Event to be trrigerred when ball is moving.
     * @return return true if the ball should explode, false otherwise
     */
    virtual bool when_ball_moving() = 0;

    /**
     * Let the shooter receive the damage.
     * @param value the damage amount
     * @return if this shooter is dead.
     */
    virtual bool receiveDamage(int value);

    virtual void whenDead(){};

    /**
     * Get health of the shooter
     *
     */
    int get_health();
};