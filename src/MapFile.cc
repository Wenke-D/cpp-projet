#include "MapFile.h"

char **map_lines_to_grid(const vector<string> &lines, unsigned int width) {
    unsigned int height = lines.size();

    // allocation of mem for a dynamic 2d array
    char **data = new char *[height];
    for (size_t i = 0; i < height; i++) {
        data[i] = new char[width];
    }

    // copy map data to a 2d array
    // for each line
    for (size_t i = 0; i < height; i++) {
        char *dst = data[i];
        string src = lines[i];
        // for each char
        for (size_t j = 0; j < width; j++) {
            if (j < src.size()) {
                dst[j] = src[j];
            } else {
                dst[j] = EMPTY_CASE;
            }
        }
    }
    return data;
}

/**
 * Separate a map file into 2 parts, pictures replacement rule and map structure
 * definition.
 * @param f the file to be read
 * @param pic_def vector that will contain lines of picture replacement rule
 * @param map_structure_def vector that will contain lines of map structure
 * @return the length of the longest line in map structure definition
 */
int separateFile(ifstream &f, vector<string> &pic_def,
                 vector<string> &map_structure_def) {

    string line;
    unsigned int max_length = 0;

    while (getline(f, line)) {
        // a line begins with a lettre between 'a' and 'z' is considered
        // as a picture definition
        if (line[0] <= 'z' && line[0] >= 'a') {
            pic_def.push_back(line);
        }

        if (line[0] == CORNER) {
            map_structure_def.push_back(line);
            break;
        }
    }

    while (getline(f, line)) {
        if (line.size() > max_length) {
            max_length = line.size();
        }
        map_structure_def.push_back(line);
    }
    return max_length;
}

char regex_filename[] = "([a-z])\t([\\w\\- ]+.[\\w\\- ]+)";

void parseLine(const string &line, map<char, string> &container) {
    regex re(regex_filename);
    smatch result;

    regex_search(line, result, re);
    char symbol = result[1].str().c_str()[0];
    string filename = result[2].str();

    container[symbol] = filename;
}

/**
 * Parse picture definition lines for the mapping between letters and filename.
 * @param lines picture definition lines
 * @return mapping between letters and filename
 */
map<char, string> *parsePicture(const vector<string> &lines) {
    map<char, string> *res = new map<char, string>();

    for (string line : lines) {
        parseLine(line, *res);
    }

    return res;
}

MapFile *MapFile::init(string filename) {
    ifstream f(filename);

    int max_length = 0;
    string line;
    vector<string> picture_lines;
    vector<string> map_structure_lines;
    if (f.is_open()) {
        max_length = separateFile(f, picture_lines, map_structure_lines);
    } else {
        cerr << "Failed to open file: " << filename << endl;
        exit(0);
    }

    const int width = max_length;
    int height = map_structure_lines.size();

    char **data = map_lines_to_grid(map_structure_lines, width);

    map<char, string> *res = parsePicture(picture_lines);

    return new MapFile(res, data, height, width);
}

ostream &operator<<(ostream &os, const MapFile &mf) {
    os << "picture:" << endl;
    for (auto e : *(mf.picture)) {
        os << e.first << ": " << e.second << endl;
    }
    os << "map structure:" << endl;
    for (size_t i = 0; i < mf.height; i++) {
        for (size_t j = 0; j < mf.width; j++) {
            os << mf.data[i][j];
        }
        os << endl;
    }

    return os;
}