#include "Labyrinthe.h"

template <typename T> T *arrayFromVector(vector<T> *v);

const int PICTURE_OFFSET = 2;

Sound *Chasseur::_hunter_fire; // bruit de l'arme du chasseur.
Sound *Chasseur::_hunter_hit;  // cri du chasseur touché.
Sound *Chasseur::_wall_hit;    // on a tapé un mur.

Environnement *Environnement::init(char *filename) {
    return new Labyrinthe(filename);
}

/**
 * Scale grid value up to rendring pixel
 * @param v the value to be scaled up
 */
inline int scale_up(int v) { return v * Environnement::scale; }

/**
 * Normalize value from rendring pixel to grid value
 * @param v the value to be normalized
 */
inline int normalize(int v) { return (int)(v / Environnement::scale); }

Labyrinthe::Labyrinthe(char *filename) {
    // configurations of res path
    modele_dir = MODELE_DIR.c_str();
    texture_dir = TEXTURE_DIR.c_str();

    MapData *map = MapData::init(filename);

    _data = map->map_file->data;
    _width = map->map_file->width;
    _height = map->map_file->height;
    cout << "Map width: " << _width << " height: " << _height << endl;
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
    _treasor._y = map->treasure->y;
}

void Labyrinthe::renderGuards(MapData *map) {
    // le chasseur et les 4 gardiens.
    _nguards = map->guards->size() + 1;

    Bridge* bridge = new Bridge(Environnement::scale);

    _guards = new Mover *[_nguards];
    Chasseur* hunter = new Chasseur(this,bridge, map->hunter->x, map->hunter->y);
    _guards[0] = hunter;
    bridge->updateHunterLocation(hunter->_x, hunter->_y);

    vector<Decoration> data = *(map->guards);
    for (int i = 0; i < _nguards - 1; i++) {
        auto src = data[i];
        char *tmp = new char[128];
        strcpy(tmp, src.texture.c_str());
        _guards[i + 1] =
            new Gardien(this,bridge, tmp, scale_up(src.l.x), scale_up(src.l.y));
    }
}

void Labyrinthe::setObstacles() {
    /* every case is empty by default */
    for (size_t i = 0; i < _width; i++) {
        for (size_t j = 0; j < _height; j++) {
            _data[i][j] = EMPTY;
        }
    }
    /* walls are obstacles */
    for (int i = 0; i < _nwall; i++) {
        Wall w = _walls[i];
        for (int x = w._x1; x <= w._x2; x++) {
            for (int y = w._y1; y <= w._y2; y++) {
                _data[x][y] = FILL;
            }
        }
    }

    // les caisses
    for (int i = 0; i < _nboxes; i++) {
        _data[_boxes[i]._x][_boxes[i]._y] = FILL;
    }

    // le trésor.
    _data[_treasor._x][_treasor._y] = FILL;

    // // les gardiens.
    // for (int i = 1; i < _nguards; i++) {
    //     int x = (int)(_guards[i]->_x / scale);
    //     int y = (int)(_guards[i]->_y / scale);
    //     _data[x][y] = FILL;
    // }
}

template <typename T> T *arrayFromVector(vector<T> *v) {
    T *array = new T[v->size()];
    std::copy(v->begin(), v->end(), array);
    return array;
}
