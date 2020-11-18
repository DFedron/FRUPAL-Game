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

  map = new Map(viewport, gamemenu);
  //map->load_map();

  tool_belt = NULL;
  curr_item = NULL;

  init_pair(5,COLOR_WHITE,COLOR_CYAN); //Royal Diamond
}

void Hero::update_display() {
  // TODO add in a scrolling mechanism, will change
  //  (print_map(y, x) & update_hero(y, x)
  map->update_display();

  update_hero();
  update_gamemenu();

  wrefresh(viewport);
  wrefresh(gamemenu);
  refresh();
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

void Hero::update_hero() {

  wattron(viewport, COLOR_PAIR(6));
  mvwaddch(viewport, ypos, xpos, '@');
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

