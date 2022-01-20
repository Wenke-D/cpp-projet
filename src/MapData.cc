#include "MapData.h"

const int PICTURE_OFFSET = 2;


/**
 * Algorithm that searchs walls and pictures in a array.
 *
 * @param data thr char array in which we looking for walls.
 * @param length length of the array
 * @param wallRep the char represention of the wall, for example '|' or '-'
 * @param rules picture replacement rules
 * @param pictures the container where will append index of the pictures in the
 * wall
 * @return a vector of location, the even index are locations of the beginning
 * of wall, odd index are respective locations of the end of wall.
 */
vector<int> *wallsAndPicturesInArray(char *data, int length, char wallRep,
                                     map<char, string> &rules,
                                     vector<int> &pictures) {
    bool withinWall = false;
    vector<int> *points = new vector<int>;

    for (int i = 0; i < length; i++) {
        char ch = data[i];
        // cout << "\tindex is " << i << endl;

        // within a wall
        if (withinWall) {
            // cout << "\t\twe are within Wall" << endl;
            // symbol to determine
            if (ch == CORNER) {
                /* Conditions to ignore this '+',
                 * that is, this '+' is not the end of the array
                 * and it's followed by some valid wall componants.
                 */
                // cout << "\t\tmeet a cornor" << endl;
                if (i != length - 1 &&
                    (data[i + 1] == wallRep || data[i + 1] == CORNER)) {
                    // cout << "\t\tignore this cornor" << endl;
                    continue;
                }
                // cout << "\t\tthis corner is a end point" << endl;
                points->push_back(i);
                withinWall = false;
            }
            // if letter is a picture symbol
            auto iter = rules.find(ch);
            if (iter != rules.end()) {
                pictures.push_back(i);
            }
        }
        // out of a wall
        else {
            // cout << "\t\twe are in outside of wall" << endl;
            // begin of a wall
            if (ch == CORNER && (i == 0 || data[i - 1] != wallRep)) {
                // cout << "\t\tthis is a begin point" << endl;
                withinWall = true;
                points->push_back(i);
            }
        }
    }

    if (withinWall) {
        // cout << "\t\t end of search within wall" << endl;
        points->pop_back();
    }

    return points;
}

/**
 * Find vertical walls in the grid.
 * @param data the grid to search
 * @param height height of the grid, length of char*
 * @param width width of the grid, length of char**
 * @return a vector of all walls in tas
 */
vector<Wall> *findHorizontalWallsAndPictures(char **data, int height, int width,
                                             map<char, string> &rules,
                                             vector<Picture> &pictures) {
    vector<Wall> *walls = new vector<Wall>;

    int length = width;

    for (int y = 0; y < height; y++) {
        char row[length];
        // copy row data into an array
        for (int j = 0; j < length; j++) {
            row[j] = data[j][y];
        }
        cout << "Finding horizontal wall in line " << (int)y << endl;

        vector<int> picture_points;
        vector<int> points = *wallsAndPicturesInArray(
            row, length, HORIZONTAL_WALL, rules, picture_points);

        // walls
        for (size_t i = 0; i < points.size(); i += 2) {
            int begin_x = points[i];
            int end_x = points[i + 1];
            walls->push_back({begin_x, y, end_x, y, 0});
        }
        // pictures
        for (int index : picture_points) {
            char sym = row[index];
            int x1 = index, x2 = x1 + PICTURE_OFFSET;
            int y1 = y, y2 = y;
            string filename = rules[sym];
            Picture p = {x1, y1, x2, y2, filename};
            pictures.push_back(p);
        }
    }
    return walls;
}

vector<Wall> *findVerticalWalls(char **data, int height, int width,
                                map<char, string> &rules,
                                vector<Picture> &pictures) {
    vector<Wall> *walls = new vector<Wall>;

    int length = height;

    for (int x = 0; x < width; x++) {
        char *col = data[x];
        cout << "Finding vertical wall in col " << x << endl;
        vector<int> picture_points;
        vector<int> points = *wallsAndPicturesInArray(
            col, length, VERTICAL_WALL, rules, picture_points);

        // constrcut walls
        for (size_t i = 0; i < points.size(); i += 2) {
            int begin_y = points[i];
            int end_y = points[i + 1];
            walls->push_back({x, begin_y, x, end_y, 0});
        }
        // construct pictures
        for (int index : picture_points) {
            char sym = col[index];
            int x1 = x, x2 = x;
            int y1 = index, y2 = index + PICTURE_OFFSET;
            string filename = rules[sym];
            Picture p = {x1, y1, x2, y2, filename};
            pictures.push_back(p);
        }
    }
    return walls;
}

/**
 * Concate elements of the second vector to the first one.
 */
template <typename T> void concatVectors(vector<T> *v1, vector<T> *v2) {
    v1->insert(v1->end(), v2->begin(), v2->end());
}

vector<Wall> *findWallsAndPictures(char **data, int height, int width,
                                   map<char, string> &rules,
                                   vector<Picture> &pictures) {
    cout << "begin finding wall in width: " << width << " height: " << height
         << endl;
    vector<Wall> *all = new vector<Wall>;

    auto v1 = findVerticalWalls(data, height, width, rules, pictures);
    auto v2 =
        findHorizontalWallsAndPictures(data, height, width, rules, pictures);

    concatVectors(all, v1);
    concatVectors(all, v2);
    return all;
}

MapData *MapData::init(string filename) {
    MapFile *map_file = MapFile::init(filename);

    vector<Picture> *pictures = new vector<Picture>;

    vector<Wall> *walls =
        findWallsAndPictures(map_file->data, map_file->height, map_file->width,
                             *(map_file->picture), *pictures);

    cout << "all pictures" << endl;
    for (auto &p : *pictures) {
        cout << p << endl;
    }

    // vector<Picture> *pictures = new vector<Picture>;
    // pictures->push_back({4, 0, 6, 0, "p1.gif"});
    // pictures->push_back({8, 0, 10, 0, "voiture.jpg"});

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

    return new MapData(walls, guards, boxes, pictures, marks, hunter, treasure,
                       map_file);
}