#include "Labyrinthe.h"
#include "Chasseur.h"
#include "Gardien.h"

Sound *Chasseur::_hunter_fire; // bruit de l'arme du chasseur.
Sound *Chasseur::_hunter_hit;  // cri du chasseur touché.
Sound *Chasseur::_wall_hit;    // on a tapé un mur.

Environnement *Environnement::init(char *filename) {
    return new Labyrinthe(filename);
}

Labyrinthe::Labyrinthe(char *filename) {
    // global configurations
    this->modele_dir = MODELE_DIR.c_str();
    this->texture_dir = TEXTURE_DIR.c_str();
    this->renderWall();
    this->renderPictures();
    this->renderBoxes();
    this->renderMarks();
    this->renderTreasure();
    this->renderGuards();
    setObstacles();
}

void Labyrinthe::renderWall() {
    // les 4 murs.
    static Wall walls[] = {
        {0, 0, LAB_WIDTH - 1, 0, 0},
        {LAB_WIDTH - 1, 0, LAB_WIDTH - 1, LAB_HEIGHT - 1, 0},
        {LAB_WIDTH - 1, LAB_HEIGHT - 1, 0, LAB_HEIGHT - 1, 0},
        {0, LAB_HEIGHT - 1, 0, 0, 0},
    };

    // les 4 murs.
    _nwall = 4;
    _walls = walls;
}
void Labyrinthe::renderPictures() {
    // une affiche.
    //  (attention: pour des raisons de rapport d'aspect, les affiches doivent
    //  faire 2 de long)
    static Wall affiche[] = {
        {4, 0, 6, 0, 0},  // première affiche.
        {8, 0, 10, 0, 0}, // autre affiche.
    };
    // deux affiches.
    _npicts = 2;
    _picts = affiche;

    // la deuxième à une texture différente.
    char tmp[128];
    // sprintf(tmp, "%s/%s", texture_dir, "voiture.jpg");
    strcpy(tmp, get_texture_path("voiture.jpg").c_str());
    _picts[1]._ntex = wall_texture(tmp);
}
void Labyrinthe::renderBoxes() {
    // 3 caisses.
    static Box caisses[] = {
        {70, 12, 0},
        {10, 5, 0},
        {65, 22, 0},
    };

    // 3 caisses.
    _nboxes = 3;
    _boxes = caisses;

    char tmp[128];

    /* DEB - NOUVEAU */
    // mettre une autre texture à la deuxième caisse.
    strcpy(tmp, get_texture_path("boite.jpg").c_str());
    caisses[1]._ntex = wall_texture(tmp);
}

void Labyrinthe::renderMarks() {
    // 2 marques au sol.
    static Box marques[] = {
        {50, 14, 0},
        {20, 15, 0},
    };

    // la deuxième à une texture différente.
    char tmp[128];

    // mettre les marques au sol.
    strcpy(tmp, get_texture_path("p1.gif").c_str());
    marques[0]._ntex = wall_texture(tmp);

    strcpy(tmp, get_texture_path("p3.gif").c_str());
    marques[1]._ntex = wall_texture(tmp);
    _nmarks = 2;
    _marks = marques;
}
void Labyrinthe::renderTreasure() {
    // le trésor.
    _treasor._x = 10;
    _treasor._y = 10;
}
void Labyrinthe::renderGuards() {
    // le chasseur et les 4 gardiens.
    _nguards = 5;
    _guards = new Mover *[_nguards];
    _guards[0] = new Chasseur(this);
    _guards[1] = new Gardien(this, "Lezard");
    _guards[2] = new Gardien(this, "Blade");
    _guards[2]->_x = 90.;
    _guards[2]->_y = 70.;
    _guards[3] = new Gardien(this, "Serpent");
    _guards[3]->_x = 60.;
    _guards[3]->_y = 10.;
    _guards[4] = new Gardien(this, "Samourai");
    _guards[4]->_x = 130.;
    _guards[4]->_y = 100.;
}

void Labyrinthe::setObstacles() {
    // set where player can go
    // autour des mur
    for (int i = 0; i < LAB_WIDTH; ++i) {
        for (int j = 0; j < LAB_HEIGHT; ++j) {
            if (i == 0 || i == LAB_WIDTH - 1 || j == 0 || j == LAB_HEIGHT - 1)
                _data[i][j] = FILL;
            else
                _data[i][j] = EMPTY;
        }
    }

    // les caisses
    for (int i = 0; i < _nboxes; i++) {
        _data[_boxes[i]._x][_boxes[i]._y] = FILL;
    }

    // le trésor.
    _data[_treasor._x][_treasor._y] = FILL;

    // les gardiens.
    for (int i = 1; i < _nguards; i++) {
        int x = (int)(_guards[i]->_x / scale);
        int y = (int)(_guards[i]->_y / scale);
        _data[x][y] = FILL;
    }
}