/*  a re do that I'm making
    maybe it'll be accepted, maybe it won't
    should be loaded onto the hero branch
    November 17, 2020
*/

#define KSIZE 128 // defines kingdom size

class item; // pre declaration

enum terrain {NONE, MEADOW, SWAMP, WATER, WALL, UNSEEN};

struct grovnick {

  enum terrain square;
  bool viewed;
  item * feature;

};

class Map {

  public:

  Map(WINDOW * vp, WINDOW * gm);

  void update_display(); // updates viewport
  int energy_cost(int y, int x); // ret -1 if off map, wall, water, 2-swamp, 1-meadow


  private:
    
    grovnick frupal[KSIZE][KSIZE];

    WINDOW * viewport;
    WINDOW * gamemenu;

};
