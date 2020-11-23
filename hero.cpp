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
Hero::Hero(WINDOW * vp, WINDOW * gm) {

  xpos = 15;
  ypos = 15;
  whiffles = 1000;
  energy = 100;
  binoculars = false;

  gamemenu = gm;
  viewport = vp;

  // creates map from input file folder
  char loadfile[] = "inputfiles/terrain.txt";
  map = new Map(viewport, gamemenu, loadfile); // implementation in map.h/cpp

  tool_belt = NULL; // empty tool belt
  curr_item = NULL; // empty curr_item(to be passed up from map)
}

//Hero::Hero(WINDOW * vp, WINDOW * gm, char * filename) {
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
  update_hero(starty, startx); // prints hero based off scroll shift #s

  update_gamemenu(); // erases and reprints gamemenu

  wrefresh(viewport); // refreshes viewport
  wrefresh(gamemenu); // refreshes game menu
}

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
void Hero::scroll_function(int& starty, int& startx) {

  int centerx, endx, centery, endy, rows, cols;

  getmaxyx(viewport, rows, cols); // find center of viewport
  centery = rows / 2;
  centerx = cols / 2;

  // finds beg and end of x-axis of viewport
  startx = xpos - centerx;
  endx = xpos + centerx;

  // makes sure we don't go out of bounds
  if(cols >= KSIZE)
    startx = 0;
  else if(startx < 0)
    startx = 0;
  else if(endx > KSIZE)
    startx = KSIZE - cols;

  // finds beg and end of y-axis of viewport
  starty = ypos - centery;
  endy = ypos + centery;

  // makes sure we don't go out of bounds
  if(rows >= KSIZE)
    starty = 0;
  else if(starty < 0)
    starty = 0;
  else if(endy > KSIZE) {
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
  if((cost = map->energy_cost(ypos, xpos)) == -1) {
    ++ypos;
    --energy;

  }
  else
    energy -= cost;
   
  update_display();

  if(map->has_item(ypos,xpos))
       map->print_item(gamemenu, ypos,xpos);

}

void Hero::move_down() {
  int cost;
  
  ++ypos;
  if((cost = map->energy_cost(ypos, xpos)) == -1) {
    --ypos;
    --energy;
  }
  else
    energy -= cost;

  update_display();

  if(map->has_item(ypos,xpos))
       map->print_item(gamemenu, ypos,xpos);

}

void Hero::move_left() {
  int cost;

  --xpos;
  if((cost = map->energy_cost(ypos, xpos)) == -1) {
    ++xpos;
    --energy;
  }
  else
    energy -= cost;

  update_display();

  if(map->has_item(ypos,xpos))
       map->print_item(gamemenu, ypos,xpos);

}

void Hero::move_right() {
  int cost;

  ++xpos;
  if((cost = map->energy_cost(ypos, xpos)) == -1) {
    --xpos;
    --energy;
  }
  else
    energy -= cost;

  update_display();
 
 if(map->has_item(ypos,xpos))
       map->print_item(gamemenu, ypos,xpos);

}

////////////////////////////////////////////////////////////////////////////////

