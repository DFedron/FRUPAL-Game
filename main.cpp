//CS300 Fall Term 2020
//Group 7
//Kingdom of Frupal

//Sources:
//https://www.linuxjournal.com/content/programming-color-ncurses
//http://www.cs.ukzn.ac.za/~hughm/os/notes/ncurses.html#input

#include "hero.h"
#include "map.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ncurses.h>

using namespace std;

int main(int argc, char ** argv)
{
  Hero * hero;
  WINDOW * viewport, * in_game;
  int ch;
  
  initscr();
  noecho();
  nodelay(stdscr, true);
  keypad(stdscr, true);
  curs_set(0);

  int igheight, igwidth = 40, vpheight, vpwidth;
  vpheight = LINES;
  igheight = LINES;
  vpwidth = COLS - igwidth;

  // added in as a 'cheat' to not fix a bug
  if(vpwidth > KSIZE) {
    vpwidth = KSIZE;
    igwidth = COLS - vpwidth;
  }

  viewport = newwin(vpheight, vpwidth, 0, 0);
  in_game = newwin(igheight, igwidth, 0, vpwidth + 1);
  wborder(in_game, '#', 0, ' ', ' ', '#', 0, '#', 0); // should put just on left side

  start_color(); // colors are matched to enum #'s
  init_pair(1,COLOR_BLACK,COLOR_GREEN);   // MEADOW = 1
  init_pair(2,COLOR_BLACK,COLOR_MAGENTA); // SWAMP = 2
  init_pair(3,COLOR_BLACK,COLOR_BLUE);    // WATER = 3
  init_pair(4,COLOR_BLACK,COLOR_WHITE);   // WALLS = 4
  init_pair(5,COLOR_BLACK,COLOR_BLACK);   // UNSEEN = 5
  init_pair(6,COLOR_YELLOW,COLOR_RED); //hero
  init_pair(7,COLOR_WHITE,COLOR_CYAN); //Royal Diamond
// implementation is down on the bottom    
  hero = new Hero(stdscr, viewport, in_game);
 
  refresh();
  hero->update_display();
  while ((ch = getch()) != 'q' && ch != 'Q')
  {
    switch (ch)
    {
      case KEY_LEFT: // move left
        hero->move_left();
        break;
      case KEY_RIGHT:
        hero->move_right();
        break;
      case KEY_UP:
        hero->move_up();
        break;
      case KEY_DOWN:
        hero->move_down();
        break;
    }
  }

    endwin();
    return 0;
}
