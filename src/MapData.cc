#include "MapData.h"

MapData *MapData::init(string filename) {
    vector<Wall> *walls = new vector<Wall>;
    walls->push_back({0, 0, LAB_WIDTH - 1, 0, 0});
    walls->push_back({LAB_WIDTH - 1, 0, LAB_WIDTH - 1, LAB_HEIGHT - 1, 0});
    walls->push_back({LAB_WIDTH - 1, LAB_HEIGHT - 1, 0, LAB_HEIGHT - 1, 0});
    walls->push_back({0, LAB_HEIGHT - 1, 0, 0, 0});

    vector<Picture> *pictures = new vector<Picture>;
    pictures->push_back({4, 0, 6, 0, "p1.gif"});
    pictures->push_back({8, 0, 10, 0, "voiture.jpg"});

    vector<Location> *boxes = new vector<Location>();
    boxes->push_back({70, 12});
    boxes->push_back({10, 5});
    boxes->push_back({65, 22});

    vector<Decoration> *marks = new vector<Decoration>;
    marks->push_back({50, 14, "p2.gif"});
    marks->push_back({20, 15, "p3.gif"});

    Location *hunter = new Location{10, 20};
    Location *treasure = new Location{1, 10};

    vector<Decoration> *guards = new vector<Decoration>;
    guards->push_back({200, 50, "Lezard"});
    guards->push_back({90, 70, "Blade"});
    guards->push_back({60, 10, "Serpent"});
    guards->push_back({130, 100, "Samourai"});

    return new MapData(walls, guards, boxes, pictures, marks, hunter, treasure);
}