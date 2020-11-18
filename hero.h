/*  This is a potential design for the Hero class
    being designed for the frupal project
    cs300 Group 7
    November 16, 2020
*/

#include <ncurses.h>

class Item; // pre declaration
class Map; // another pre declaration

class Hero {

  public:
    
    Hero() =delete;
    Hero(WINDOW * std, WINDOW * vp, WINDOW * gm);
//    Hero(WINDOW * std, WINDOW * vp, WINDOW * gm, char * filename);

    void update_display();

    void move_up();
    void move_down();
    void move_left();
    void move_right();

  private:
    
    int xpos;
    int ypos;
    int whiffles;
    int energy;
    bool binoculars;

    Map * map;

    Item * tool_belt;
    Item * curr_item; // maybe can use for item interaction?...

    WINDOW * viewport;
    WINDOW * gamemenu;
    WINDOW * stdwindow;

    void update_hero(int starty, int startx);
    void update_gamemenu();
    void scroll_function(int& starty, int& startx);
  
};
