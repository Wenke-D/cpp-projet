#ifndef M1_CPP_PROJECT_MAP_FILE
#define M1_CPP_PROJECT_MAP_FILE

#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

using namespace std;

const char CORNER = '+';
const char HORIZONTAL_WALL = '-';
const char VERTICAL_WALL = '|';
const char HUNTER = 'C';
const char GUARD = 'G';
const char TREASURE = 'T';
const char BOX = 'x';
const char EMPTY_CASE = ' ';

class MapFile {
  public:
    map<char, string> *picture;
    char **data;
    unsigned int height, width;


    MapFile(map<char, string> *picture, char **data, unsigned int height,
            unsigned int width)
        : picture(picture), data(data), height(height), width(width){};

    ~MapFile();

    /**
     * Instancize an object from a valid map file.
     * This method does not check validty of the input map file.
     * @param filename the full path of input file.
     * @return a corresponding object
     */
    static MapFile *init(string filename);

    friend ostream &operator<<(ostream &os, const MapFile &mf);
};

#endif