#include "MapData.h"
#include "toString.h"




/**
 * Algorithm that findd walls in a array.
 *
 * @param wallRep the char represention of the wall, for example '|' or '-'
 * @return a vector of location, the even index are locations of the beginning
 * of wall, odd index are respective locations of the end of wall.
 */
vector<int> *wallsInArray(char *data, int length, char wallRep) {
    bool withinWall = false;
    vector<int> *points = new vector<int>;

    for (int i = 0; i < length; i++) {
        char ch = data[i];
        // cout << "\tindex is " << i << endl;
        ;
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
        // cout << "\t\tend of search within wall" << endl;
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
vector<Wall> *findHorizontalWalls(char **data, int height, int width) {
    vector<Wall> *walls = new vector<Wall>;

    int length = width;

    for (int y = 0; y < height; y++) {
        char row[length];
        // copy row data into an array
        for (int j = 0; j < length; j++) {
            row[j] = data[j][y];
        }
        cout << "Finding horizontal wall in line " << y << endl;
        vector<int> points = *wallsInArray(row, length, HORIZONTAL_WALL);
        for (size_t i = 0; i < points.size(); i += 2) {
            int begin_x = points[i];
            int end_x = points[i + 1];
            walls->push_back({begin_x, y, end_x, y, 0});
        }
    }
    return walls;
}

vector<Wall> *findVerticalWalls(char **data, int height, int width) {
    vector<Wall> *walls = new vector<Wall>;

    int length = height;

    for (int x = 0; x < width; x++) {
        char *col = data[x];
        cout << "Finding vertical wall in col " << x << endl;
        vector<int> points = *wallsInArray(col, length, VERTICAL_WALL);

        for (size_t i = 0; i < points.size(); i += 2) {
            int begin_y = points[i];
            int end_y = points[i + 1];
            walls->push_back({x, begin_y, x, end_y, 0});
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

vector<Wall> *findWalls(char **data, int height, int width) {
    cout << "begin finding wall in width: " << width << " height: " << height
         << endl;
    vector<Wall> *all = new vector<Wall>;

    auto v1 = findVerticalWalls(data, height, width);
    auto v2 = findHorizontalWalls(data, height, width);

    concatVectors(all, v1);
    concatVectors(all, v2);
    return all;
}

MapData *MapData::init(string filename) {
    MapFile *map_file = MapFile::init(filename);

    vector<Wall> *walls =
        findWalls(map_file->data, map_file->height, map_file->width);

    cout << "All the walls: " << endl;
    cout << *walls << endl;

    vector<Picture> *pictures = new vector<Picture>;
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