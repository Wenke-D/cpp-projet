#include "config.h"

const string SEP = "/";

const string RES_DIR = "res";

const string SOUND_DIR = RES_DIR + SEP + "sons";

const string TEXTURE_DIR = RES_DIR + SEP + "textures";

const string MODELE_DIR = RES_DIR + SEP + "modeles";

extern const int HUNTER_HEALTH = 100;

extern const int GUARDIEN_HUEALTH = 50;

string get_sound_path(const string &name) { return SOUND_DIR + SEP + name; }

string get_texture_path(const string &name) { return TEXTURE_DIR + SEP + name; }

string get_modele_path(const string &name) { return MODELE_DIR + SEP + name; }