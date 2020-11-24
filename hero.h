/*  This is a potential design for the Hero class
    being designed for the frupal project
    cs300 Group 7
    November 16, 2020
*/

#include <ncurses.h>
#include <string>
using namespace std;

class Item; // pre declaration
class Map; // another pre declaration

class Hero {

  public:
    
//    Hero() =delete; // don't need a default constructor
    Hero(WINDOW * vp, WINDOW * gm); // constructor
    // TODO create this constructor down here for alternate maps
//    Hero(WINDOW * vp, WINDOW * gm, char * filename);

    void update_display(); // updates hero on viewport after map

    void move_up(); // moves hero up, updates display
    void move_down(); // same
    void move_left();
    void move_right();
    
     // returns true if energy is 0 or less, returns false otherwise
    bool check_energy(); // check hero's energy    
    void add_energy(int en); 
    
    void engage_item(int ypos, int xpos);
    bool tool_match(Item *& curr_tool, string type);   
    void print_tool_belt(Item * t_belt, int row);
    
  private:
    
    int ypos; // hero's pos from top
    int xpos; // hero's pos from left
    int whiffles; // hero's whiffles
    int energy; // hero's energy
    bool binoculars; // if true, can see 2, otherwise see 1

    Map * map; // map object that contains all the functionality for 2D grid

    Item * tool_belt; // will be LLL of Tool class
    Item * curr_item; // use for interaction, passed up from map

    WINDOW * viewport; // to have control of vp
    WINDOW * gamemenu; // to have control of gm

    // takes in scroll parameters, starty, startx, prints hero on screen accoringly
    void update_hero(int starty, int startx); // updates hero on screen
    void update_gamemenu(); // prints the standard game menu w/ whiffles/energy
    void scroll_function(int& starty, int& startx); // determines starty, startx
    // so we know where to start printing the map and hero relative to viewport
  
};
