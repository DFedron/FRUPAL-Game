/*  This is a potential design for the Hero class
    being designed for the frupal project
    cs300 Group 7
    November 16, 2020
*/

#include <ncurses.h>
#include <string.h>

#include "hero.h"
#include "item_tiles.h"
#include "map.h"

Hero::Hero(WINDOW * std, WINDOW * vp, WINDOW * gm) {

  
  xpos = 15;
  ypos = 15;
  whiffles = 1000;
  energy = 100;
  binoculars = false;

  stdwindow = std;
  gamemenu = gm;
  viewport = vp;

  char loadfile[] = "inputfile/terrain.txt";
  map = new Map(viewport, gamemenu, loadfile);

  tool_belt = NULL;
  curr_item = NULL;
}

//Hero::Hero(WINDOW * std, WINDOW * vp, WINDOW * gm, char * filename) {
//
//}

void Hero::scroll_function(int& starty, int& startx) {

  int centerx, endx, centery, endy, rows, cols;

  // THIS IS THE START OF A COMPLICATED SCROLLING FUNCTION
  // it's not that complicated but worth taking a look
  getmaxyx(viewport, rows, cols);
  centery = rows / 2;
  centerx = cols / 2;

  startx = xpos - centerx;
  endx = xpos + centerx;

  if(cols >= KSIZE)
    startx = 0;
  else if(startx < 0)
    startx = 0;
  else if(endx > KSIZE)
    startx = KSIZE - cols;

  starty = ypos - centery;
  endy = ypos + centery;

  if(rows >= KSIZE)
    starty = 0;
  else if(starty < 0)
    starty = 0;
  else if(endy > KSIZE) {
    starty = KSIZE - rows;
  }
  // END OF SCROLLING MECHANISM
}

void Hero::update_display() {

  int starty, startx; // will be modified in scroll_function

  werase(viewport);
  // changes starty, startx to center hero/map
  scroll_function(starty, startx);

  map->look_around(ypos, xpos, binoculars);

  map->update_display(starty, startx);
  update_hero(starty, startx);

  update_gamemenu();

  wrefresh(viewport);
  wrefresh(gamemenu);
//  refresh();
}

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

void Hero::update_hero(int starty, int startx) {

  wattron(viewport, COLOR_PAIR(6));
  mvwaddch(viewport, ypos - starty, xpos - startx, '@');
  wattroff(viewport, COLOR_PAIR(6));

}

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
}

