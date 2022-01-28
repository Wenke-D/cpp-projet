#pragma once
#include "Bridge.h"
#include "Mover.h"
#include "config.h"
#include "Sound.h"



const string HUNTER_FIRE_SOUND_PATH = get_sound_path("hunter_fire.wav");
const string HUNTER_HIT_SOUND_PATH = get_sound_path("hunter_hit.wav");
const string HIT_WALL_SOUND_PATH = get_sound_path("hit_wall.wav");

class Shooter : public Mover {
  public:

    // les sons.
    static Sound *_hunter_fire; // bruit de l'arme du chasseur.
    static Sound *_hunter_hit;  // cri du chasseur touché.
    static Sound *_wall_hit;    // on a tapé un mur.

    Bridge *bridge;

    Shooter(int x, int y, Labyrinthe *l, const char *modele, Bridge *bridge)
        : Mover(x, y, l, modele), bridge(bridge){
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
     * fait tirer le personnage sur un ennemi (vous pouvez ignorer l'angle
     * vertical).
     */
    virtual void fire(int angle_vertical) override;

    /**
     * Event to trigger after the ball exploded.
     */
    virtual void after_explonation(){}

    /**
     * Event to trriger when ball is moving.
     * 
     */
    virtual void when_ball_moving(){}
};