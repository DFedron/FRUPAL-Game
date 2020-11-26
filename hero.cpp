/*  This is a potential design for the Hero class
    being designed for the frupal project
    cs300 Group 7
    November 16, 2020
*/

#include <ncurses.h>
#include <string.h>

#include "hero.h"
#include "map.h"

// our 'defaul constructor'
Hero::Hero(WINDOW *vp, WINDOW *gm) {

  xpos = 15;
  ypos = 15;
  whiffles = 1000;
  energy = 100;
  binoculars = false;
  ship = false;
  diamond = false;

  gamemenu = gm;
  viewport = vp;

  // creates map from input file folder
  char loadfile[] = "inputfiles/terrain.txt";
  map = new Map(viewport, gamemenu, loadfile); // implementation in map.h/cpp

  tool_belt = NULL; // empty tool belt
  curr_item = NULL; // empty curr_item(to be passed up from map)
}

// Hero::Hero(WINDOW * vp, WINDOW * gm, char * filename) {
//
//}

////////////////////////////////////////////////////////////////////////////////
/*
    These are our display functions.  scroll_function centers hero in map, and
    makes sure viewport doesn't go out of bounds. update_gamemenu prints the
    standard game menu. update_hero prints the hero with scroll mechanism
*/
////////////////////////////////////////////////////////////////////////////////

// updates display, kind of a wrapper function
void Hero::update_display() {

  int starty, startx; // will be modified in scroll_function

  werase(viewport); // resets viewport
  // changes starty, startx to center hero/map
  scroll_function(starty, startx);

  map->look_around(ypos, xpos, binoculars); // updates map to new view

  map->update_display(starty, startx); // prints map based off scroll shift #s
  update_hero(starty, startx);         // prints hero based off scroll shift #s

  update_gamemenu(); // erases and reprints gamemenu

  wrefresh(viewport); // refreshes viewport
  wrefresh(gamemenu); // refreshes game menu
}

// returns true if dead, false otherwise
bool Hero::check_energy() {
  if (energy < 1)
    return true;
  else
    return false;
}

void Hero::add_energy(int en) { energy += en; }

// just erases and redraws the basic gamemenu
void Hero::update_gamemenu() {

  int rows, cols;
  getmaxyx(gamemenu, rows, cols);

  werase(gamemenu);
  wborder(gamemenu, '#', 0, ' ', ' ', '#', 0, '#', 0);

  // XXX remove these 3 lines, all testing stuff
  mvwprintw(gamemenu, rows - 6, 2, "This is for testing:");
  mvwprintw(gamemenu, rows - 5, 2, "x-position: %d", xpos);
  mvwprintw(gamemenu, rows - 4, 2, "y-position: %d", ypos);

  mvwprintw(gamemenu, 1, 1, "Menu:");
  mvwprintw(gamemenu, rows - 3, 2, "Energy: %d", energy);
  mvwprintw(gamemenu, rows - 2, 2, "Whiffles: %d", whiffles);
}

// places the hero on the viewport, shifts by starty and startx
// which are measured with scroll function, puting hero in center
// or bound by 0 or KSIZE in map.
void Hero::update_hero(int starty, int startx) {

  wattron(viewport, COLOR_PAIR(6));
  mvwaddch(viewport, ypos - starty, xpos - startx, '@');
  wattroff(viewport, COLOR_PAIR(6));
}

// THIS IS THE START OF A COMPLICATED SCROLLING FUNCTION
// it's not that complicated but worth taking a look
void Hero::scroll_function(int &starty, int &startx) {

  int centerx, endx, centery, endy, rows, cols;

  getmaxyx(viewport, rows, cols); // find center of viewport
  centery = rows / 2;
  centerx = cols / 2;

  // finds beg and end of x-axis of viewport
  startx = xpos - centerx;
  endx = xpos + centerx;

  // makes sure we don't go out of bounds
  if (cols >= KSIZE)
    startx = 0;
  else if (startx < 0)
    startx = 0;
  else if (endx > KSIZE)
    startx = KSIZE - cols;

  // finds beg and end of y-axis of viewport
  starty = ypos - centery;
  endy = ypos + centery;

  // makes sure we don't go out of bounds
  if (rows >= KSIZE)
    starty = 0;
  else if (starty < 0)
    starty = 0;
  else if (endy > KSIZE) {
    starty = KSIZE - rows;
  }
  // END OF SCROLLING MECHANISM
}

////////////////////////////////////////////////////////////////////////////////
/*  updates hero pos.  if map->energy_cost(y,x) -1, it is WATER or WALL so
    resets position and costs 1 energy, otherwise drops down energy_cost
    1 for MEADOW, 2 for SWAMP.  updates display reprints entire screen with
    new positions.
*/
////////////////////////////////////////////////////////////////////////////////

void Hero::move_up() {
  int cost;

  --ypos;
  if ((cost = map->energy_cost(ypos, xpos, ship)) == -1) {
    ++ypos;
    --energy;

  } else
    energy -= cost;

  update_display();

  if (map->has_item(ypos, xpos)) {
    map->print_item(gamemenu, ypos, xpos);
    engage_item(ypos, xpos);
  }
}

void Hero::move_down() {
  int cost;

  ++ypos;
  if ((cost = map->energy_cost(ypos, xpos, ship)) == -1) {
    --ypos;
    --energy;
  } else
    energy -= cost;

  update_display();

  if (map->has_item(ypos, xpos)) {
    map->print_item(gamemenu, ypos, xpos);
    engage_item(ypos, xpos);
  }
}

void Hero::move_left() {
  int cost;

  --xpos;
  if ((cost = map->energy_cost(ypos, xpos, ship)) == -1) {
    ++xpos;
    --energy;
  } else
    energy -= cost;

  update_display();

  if (map->has_item(ypos, xpos)) {
    map->print_item(gamemenu, ypos, xpos);
    engage_item(ypos, xpos);
  }
}

void Hero::move_right() {
  int cost;

  ++xpos;
  if ((cost = map->energy_cost(ypos, xpos, ship)) == -1) {
    --xpos;
    --energy;
  } else
    energy -= cost;

  update_display();

  if (map->has_item(ypos, xpos)) {
    map->print_item(gamemenu, ypos, xpos);
    engage_item(ypos, xpos);
    //       engage_item(map->frupal[ypos][xpos]->feature);
  }
}

/// function for interacting with items
void Hero::engage_item(int ypos, int xpos) {

  // if food, tool, ship or binoculars, ask for purchase
  // if yes, subtract cost from account, add tool to belt, add ship somewhere,
  // binoculars is true, add energy to hero energy
  // after purchase, map removes item from map

  // curr_item gets item
  map->get_item(curr_item, ypos, xpos);

  // downcasting all the pointers and just seeing what fits
  Food *food_ptr = dynamic_cast<Food *>(curr_item);
  Tool *tool_ptr = dynamic_cast<Tool *>(curr_item);
  Obstacle *ob_ptr = dynamic_cast<Obstacle *>(curr_item);
  Ship *ship_ptr = dynamic_cast<Ship *>(curr_item);
  Binoculars *bino_ptr = dynamic_cast<Binoculars *>(curr_item);
  Treasure_chest *treasure_ptr = dynamic_cast<Treasure_chest *>(curr_item);
  Diamond *diamond_ptr = dynamic_cast<Diamond *>(curr_item);

  // must find one of them at least
  if (food_ptr) {
    whiffles -= curr_item->get_cost();
    energy += curr_item->get_energy();
    map->remove_item(ypos, xpos);
  } else if (tool_ptr) {
    if (!tool_belt) {
      tool_belt = new Tool(*tool_ptr);
    } else {
      Item *temp = new Tool(*tool_ptr);
      temp->get_next() = tool_belt;
      tool_belt = temp;
    }
    whiffles -= curr_item->get_cost();
  } else if (ob_ptr) {
    if (tool_belt) {
      int row = 25;
      mvwprintw(gamemenu, row, 3, "Tools in Tool Belt: ");
      print_tool_belt(tool_belt, ++row);

      string type;
      curr_item->get_type(type); // gets type of obstacle
      Item *curr_tool = tool_belt;

      if (!tool_match(curr_tool, type)) // if no tool match is found
        energy -= ob_ptr->get_energy();
    } else
      energy -= ob_ptr->get_energy();
  } else if (ship_ptr) {
    ship = true;
    // should there be a bool ship? true if you have it false if not?
  } else if (bino_ptr) {
    binoculars = true;
  } else if (treasure_ptr) {
    whiffles += treasure_ptr->get_whiffles();
  }

  else if (diamond_ptr) {
    diamond = true;
    whiffles += diamond_ptr->get_whiffles();

    // maybe temporary, maybe move to main.cpp
    // for the same endgame,so most data from main end_game_menu function
    nodelay(stdscr, false);
    WINDOW *endgame;
    endgame = newwin(20, 50, (LINES - 20) / 2, (COLS - 50) / 2);
    int c = '#';
    wborder(endgame, c, c, c, c, c, c, c, c);

    mvwprintw(endgame, 9, 20, "YOU WIN!!!");

    wrefresh(endgame);
    getch();
    endwin();
    exit(0);
  }
  curr_item = NULL;
  map->remove_item(ypos, xpos);
}

bool Hero::tool_match(Item *&curr_tool, string type) {
  if (!curr_tool)
    return false;
  string ob_type;
  curr_tool->get_obstacle_type(ob_type);

  if (type.compare(ob_type)) {
    float quotient = curr_item->get_energy() / tool_belt->get_energy();
    energy -= static_cast<int>(quotient);

    string tool_name;
    curr_tool->get_name(tool_name);
    mvwprintw(gamemenu, 20, 3, "Removed ");
    waddstr(gamemenu, ob_type.data());
    mvwprintw(gamemenu, 21, 3, " with ");
    waddstr(gamemenu, tool_name.data());
    wrefresh(gamemenu);

    // remove toolbelt item...
    if (!curr_tool->get_next()) // if there's no next tool in toolbelt
    {
      delete curr_tool;
      curr_item = NULL;
      tool_belt = NULL;
    } else {
      Item *temp = curr_tool->get_next();
      if (curr_tool == tool_belt)
        tool_belt = temp;
      delete curr_tool;
      curr_tool = temp;
      temp = NULL;
    }

    return true;
  } else
    return tool_match(curr_tool->get_next(), type);
}
void Hero::print_tool_belt(Item *t_belt, int row) {
  if (!t_belt)
    return;
  string name;
  t_belt->get_name(name);
  mvwaddstr(gamemenu, row++, 3, name.data());
  wprintw(gamemenu, ": Rating %dX", t_belt->get_energy());

  print_tool_belt(t_belt->get_next(), row);
}
////////////////////////////////////////////////////////////////////////////////
