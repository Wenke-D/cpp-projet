#pragma once

#include <iostream>
#include <string>

using namespace std;

struct Wall {
    int _x1, _y1; // point de depart.
    int _x2, _y2; // point d'arrivée.
    int _ntex;    // numéro de texture.
};

struct Box {
    int _x, _y; // emplacement.
    int _ntex;  // numéro de texture.
};

/*
 *	Traduit un fichier de type définition de labyrinthe au format interne.
 */

enum Case {
    /**
     * case vide (où on peut marcher!)
     */
    EMPTY = 0,
    /**
     * case remplit (où on ne peut pas marcher)
     */
    FILL = 1
};

class Location {
  public:
    int x, y;
    Location(int x, int y);
    ~Location(){};
    Location operator+(const Location& other) const;
    Location operator-(const Location& other) const;
};

std::ostream &operator<<(std::ostream &out, const Location &p);

class Picture {
  private:
    /* data */
  public:
    Location start;
    Location end;
    std::string image;

    Picture(Location start, Location end, std::string image);
    Picture(int x1, int y1, int x2, int y2, std::string image);

    ~Picture();
};

std::ostream &operator<<(std::ostream &out, const Picture &p);

/**
 * Decoration is the combination of texture and location.
 */
class Decoration {
  private:
  public:
    Location l;
    string texture;
    Decoration(Location location, string texture)
        : l(location), texture(texture){};
    Decoration(int x, int y, string texture) : Decoration({x, y}, texture){};
    ~Decoration(){};
};
