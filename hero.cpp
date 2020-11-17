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

  map = new Map();
  map->load_map();

  tool_belt = NULL;
  curr_item = NULL;

  init_pair(5,COLOR_WHITE,COLOR_CYAN); //Royal Diamond
}

void Hero::update_display() {
  // TODO add in a scrolling mechanism, will change
  //  (print_map(y, x) & update_hero(y, x)
  map->print_map();

  update_hero();

  wrefresh(viewport);
  refresh();
}

void Hero::update_hero() {

  wattron(viewport, COLOR_PAIR(6));
  mvwaddch(viewport, ypos, xpos, '@');
  wattroff(viewport, COLOR_PAIR(6));

}

void Hero::move_up() {
  --ypos;
  if(ypos < 0)
  {
    ++ypos;
    --energy;
  }
  update_display();
}

void Hero::move_down() {
  ++ypos;
  if(ypos >= 40)
  {
    --ypos;
    --energy;
  }
  update_display();
}

void Hero::move_left() {
  --xpos;
  if(xpos < 0)
  {
    ++xpos;
    --energy;
  }
  update_display();
}

void Hero::move_right() {
  ++xpos;
  if(xpos >= 40) // 40 for map...
  {
    --xpos;
    --energy;
  }
  update_display();
}

