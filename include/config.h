#ifndef M1_CPP_PROJECT_CONFIG
#define M1_CPP_PROJECT_CONFIG

#include <string>

using namespace std;;

extern const string RES_DIR;

extern const string SOUND_DIR;

extern const string TEXTURE_DIR;

extern const string MODELE_DIR;

/**
 * Return the full path of a sound file.
 * @param name filename of the sound with extension
 */
string get_sound_path(const string& name);

/**
 * Return the full path of a texture file.
 * @param name filename of the texture with extension
 */
string get_texture_path(const string& name);

/**
 * Return the full path of a modele file.
 * @param name filename of the modele with extension
 */
string get_modele_path(const string& name);


#endif