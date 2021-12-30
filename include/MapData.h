#ifndef M1_CPP_PROJECT_MAPDATA
#define M1_CPP_PROJECT_MAPDATA

/**
 * Data structure of a map after parsing a map file
 */

#include "Decoration.h"
#include "Environnement.h"
#include "Location.h"
#include "Picture.h"

#include <vector>

#define LAB_WIDTH 80
#define LAB_HEIGHT 25

using namespace std;

class MapData {
  public:
    vector<Wall> *walls;
    vector<Decoration> *guards;
    vector<Location> *boxes;
    vector<Picture> *pictures;
    vector<Decoration> *marks;

    Location *hunter;
    Location *treasure;

    MapData(vector<Wall> *walls, vector<Decoration> *guards,
            vector<Location> *boxes, vector<Picture> *pictures,
            vector<Decoration> *marks, Location *hunter, Location *treasure)
        : walls(walls), guards(guards), boxes(boxes), pictures(pictures),
          marks(marks), hunter(hunter), treasure(treasure){};

    /**
     * Make a mapData object from a map file.
     * @param filename the full valid path of the map file
     * @return a mapData object
     */
    static MapData *init(string filename);

    ~MapData() {
        delete walls;
        delete guards;
        delete boxes;
        delete pictures;
        delete marks;
        delete hunter;
        delete treasure;
    };
};

#endif
