#include "Labyrinthe.h"
#include "Chasseur.h"
#include "Gardien.h"

#include <iostream>

template <typename T> T *arrayFromVector(vector<T> *v);

const int PICTURE_OFFSET = 2;


Sound *Chasseur::_hunter_fire; // bruit de l'arme du chasseur.
Sound *Chasseur::_hunter_hit;  // cri du chasseur touché.
Sound *Chasseur::_wall_hit;    // on a tapé un mur.

Environnement *Environnement::init(char *filename) {
    return new Labyrinthe(filename);
}

Labyrinthe::Labyrinthe(char *filename) {
    // configurations of res path
    modele_dir = MODELE_DIR.c_str();
    texture_dir = TEXTURE_DIR.c_str();

    MapData *map = MapData::init(filename);

    renderWall(map);
    renderPictures(map);
    renderBoxes(map);
    renderMarks(map);
    renderTreasure(map);
    renderGuards(map);
    setObstacles();
}

void Labyrinthe::renderWall(MapData *map) {

    // les 4 murs.
    _nwall = map->walls->size();
    Wall *walls = arrayFromVector(map->walls);
    _walls = walls;
}

void Labyrinthe::renderPictures(MapData *map) {
    auto pics = map->pictures;
    vector<Wall> *pictures = new vector<Wall>;

    std::for_each(pics->begin(), pics->end(), [pictures, this](Picture p) {
        char *t = new char[p.image.size() + 1];
        strcpy(t, get_texture_path(p.image).c_str());

        Wall pic = {p.start.x, p.start.y, p.end.x, p.end.y, wall_texture(t)};
        pictures->push_back(pic);
    });
    // deux affiches.
    _npicts = map->pictures->size();
    _picts = arrayFromVector(pictures);
}

void Labyrinthe::renderBoxes(MapData *map) {
    // use a more beautiful box texture
    char tmp[128];
    strcpy(tmp, get_texture_path("boite.jpg").c_str());
    int texture_number = wall_texture(tmp);

    vector<Location> *boxes_info = map->boxes;
    vector<Box> *boxes = new vector<Box>;

    for (size_t i = 0; i < boxes_info->size(); i++) {
        Location l = (*boxes_info)[i];
        boxes->push_back({l.x, l.y, texture_number});
    }

    _nboxes = boxes->size();
    _boxes = arrayFromVector(boxes);
}

void Labyrinthe::renderMarks(MapData *map) {
    char tmp[128];

    vector<Box> *marks = new vector<Box>;
    for (size_t i = 0; i < map->marks->size(); i++) {
        auto e = (*(map->marks))[i];

        strcpy(tmp, get_texture_path(e.texture).c_str());
        int texture_n = wall_texture(tmp);

        marks->push_back({e.l.x, e.l.y, texture_n});
    }
    _nmarks = marks->size();
    _marks = arrayFromVector(marks);
}

void Labyrinthe::renderTreasure(MapData *map) {
    _treasor._x = map->treasure->x;
    _treasor._y = map->treasure->x;
}

void Labyrinthe::renderGuards(MapData *map) {
    // le chasseur et les 4 gardiens.
    _nguards = map->guards->size() + 1;

    _guards = new Mover *[_nguards];
    _guards[0] = new Chasseur(this);

    vector<Decoration> data = *(map->guards);
    for (int i = 0; i < _nguards - 1; i++) {
        auto src = data[i];
        cout << "index: " << i + 1 << '\n';
        char *tmp = new char[128];
        strcpy(tmp, src.texture.c_str());
        _guards[i + 1] = new Gardien(this, tmp);
        _guards[i + 1]->_x = src.l.x;
        _guards[i + 1]->_y = src.l.y;
    }
}

void Labyrinthe::setObstacles() {
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

template <typename T> T *arrayFromVector(vector<T> *v) {
    T *array = new T[v->size()];
    std::copy(v->begin(), v->end(), array);
    return array;
}
