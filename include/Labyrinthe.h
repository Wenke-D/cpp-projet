#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include <algorithm>


#include "Environnement.h"
#include "MapData.h"



class MapData;


class Labyrinthe : public Environnement {
  private:
    char _data[LAB_WIDTH][LAB_HEIGHT];

  public:
    Labyrinthe(char *);
    int width() { return LAB_WIDTH; }   // retourne la largeur du labyrinthe.
    int height() { return LAB_HEIGHT; } // retourne la longueur du labyrinthe.

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
