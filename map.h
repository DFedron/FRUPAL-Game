/*  a re do that I'm making
    maybe it'll be accepted, maybe it won't
    should be loaded onto the hero branch
    November 17, 2020
*/

#include <string>

#define KSIZE 128 // defines kingdom size
#define NUMTERRAIN 3 // defines # of terrain files

class item; // pre declaration

enum terrain {NONE, MEADOW, SWAMP, WATER, WALL, UNSEEN};

using namespace std;

struct grovnick {

  enum terrain square;
  bool viewed;
  item * feature;

};

class Map {

  public:

  Map(WINDOW * vp, WINDOW * gm);
  Map(WINDOW * vp, WINDOW * gm, char * inputfile);
  void update_display(int starty, int startx); // updates viewport
  int energy_cost(int y, int x); // ret -1 if off map, wall, water, 2-swamp, 1-meadow

  void look_around(int ypos, int xpos, bool binoculars);

  private:
    
    grovnick frupal[KSIZE][KSIZE];

    WINDOW * viewport;
    WINDOW * gamemenu;

  void load_terrain(string file);

};

