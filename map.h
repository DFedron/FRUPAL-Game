//Map.h
#include "grovnick.h"
#include <string>
#include <ncurses.h>
 
using namespace std;

const int terrain_num = 3;

class Map{
    private:
      Grovnick map[40][40];
      int map_size;
      string terrain_list[terrain_num];
      int color_value_list[terrain_num];

    public:
      Map();
      void input_color_value(); 
      void load_map();
      void load_terrain(string file,int color_value,int e_cost);
     
      void print_map();
      void print_grovnick(int i,int j);
  
      bool colors_match(int i, int j, int color_pair_value);
  
      void edit_map(int lines, int cols, WINDOW *viewport);
      void edit_terrain(int i, int j, int color_pair_value);
 
      void save_map();

//    void create_new_map(int lines, int cols, WINDOW * viewport);
// should have fresh green map and have a save file 

//    void load_items(string file);
//    ...
};
