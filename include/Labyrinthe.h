#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include <algorithm>


#include "Environnement.h"
#include "MapData.h"



class MapData;


class Labyrinthe : public Environnement {
  private:
    /* width is length of char**, height is length of char* */
    char** _data;
    unsigned int _width;
    unsigned int _height;

  public:
    Labyrinthe(char *);
    int width() { return _width; }   // retourne la largeur du labyrinthe.
    int height() { return _height; } // retourne la longueur du labyrinthe.

    /**
     * retourne la case (i, j).
     */
    char data(int i, int j) { return _data[i][j]; }


private:
	void renderWall(MapData* map);
	void renderPictures(MapData* map);
	void renderBoxes(MapData* map);
	void renderMarks(MapData* map);
	void renderTreasure(MapData* map);
	void renderGuards(MapData* map);
	/**
	 * Set where roles can't walk through.
	 */
	void setObstacles();
};

#endif
