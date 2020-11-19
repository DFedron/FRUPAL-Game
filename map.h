/*  a re do that I'm making
    maybe it'll be accepted, maybe it won't
    should be loaded onto the hero branch
    November 17, 2020
*/

#include <string>

#define KSIZE 128 // defines kingdom size
#define NUMTERRAIN 3 // defines # of terrain files

class Item; // pre declaration

enum terrain {NONE, MEADOW, SWAMP, WATER, WALL, UNSEEN};

using namespace std;

struct grovnick {

  enum terrain square; // holds enum above ^^^
  bool viewed;         // bool if viewed or no
  Item * feature;      // this will be an item

};

class Map {

  public:

  Map() =delete;
  Map(WINDOW * vp, WINDOW * gm);
  Map(WINDOW * vp, WINDOW * gm, char * inputfile);
  
  void update_display(int starty, int startx); // updates viewport
  int energy_cost(int y, int x); // ret -1 if off map, wall, water,
                                 // 2-swamp, 1-meadow

  void look_around(int ypos, int xpos, bool binoculars);

  private:
    
    grovnick frupal[KSIZE][KSIZE]; // holds 2D array of structs

    WINDOW * viewport; // easy print to viewport
    WINDOW * gamemenu; // might not need?

    void load_terrain(string file); // loads a terrain file
    void load_map(string file); // loads ALL the terrain files
};

