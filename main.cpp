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


//  WINDOW * viewport= newwin(LINES ,ncols, y0, x0);  
//  WINDOW * menu= newwin(LINES, ncols, y0,COLS-( ncols)); 
  int igheight, igwidth = 40, vpheight, vpwidth;
  vpheight = LINES;
  igheight = LINES;
  vpwidth = COLS - igwidth;

  // added in as a 'cheat' to not fix a bug
//if(vpwidth > 40) {
//  vpwidth = 40;
//  igwidth = COLS - vpwidth;
//}

  viewport = newwin(vpheight, vpwidth, 0, 0);
  in_game = newwin(igheight, igwidth, 0, vpwidth);
  wborder(in_game, '#', 0, ' ', ' ', '#', 0, '#', 0); // should put just on left side

  start_color();
  init_pair(1,COLOR_BLACK,COLOR_GREEN); //meadow
  init_pair(2,COLOR_BLACK,COLOR_MAGENTA); //swamp
  init_pair(3,COLOR_BLACK,COLOR_BLUE); //water
  init_pair(4,COLOR_BLACK,COLOR_WHITE);  //walls
  init_pair(5,COLOR_WHITE,COLOR_CYAN); //Royal Diamond
  init_pair(6,COLOR_YELLOW,COLOR_RED); //hero

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

////CREATES '#' BORDER
//    move(0,ncols);
//    vline(border,LINES);
          
//// PLACEHOLDER TEXT
//  int txt_y = 1;
//  int txt_x = ncols +1;
//  mvprintw(txt_y++,txt_x, " > Food: Steak"); 
//  mvprintw(txt_y++,txt_x, " > Cost: 10"); 
//  mvprintw(txt_y++,txt_x, " > Energy: 20"); 
//  mvprintw(txt_y++,txt_x, " Options"); 
//  mvprintw(txt_y++,txt_x, " 1) North"); 
//  mvprintw(txt_y++,txt_x, " 2) East"); 
//  mvprintw(txt_y++,txt_x, " 3) South"); 
//  mvprintw(txt_y++,txt_x, " 4) West");

////TERRAIN KEYS 
//  txt_y +=2; 
//  mvprintw(txt_y++,txt_x, " Press 'm' for meadow");
//  mvprintw(txt_y++,txt_x, " Press 's' for swamp");
//  mvprintw(txt_y++,txt_x, " Press 'w' for water");
//  mvprintw(txt_y++,txt_x, " Press 'l' for wall");
//  mvprintw(txt_y++,txt_x, " Press 'q' to exit");


////PLACEHOLDER TEXT
//  txt_y = LINES -2;
//  txt_x = ncols +1;
//  mvprintw(txt_y-1,txt_x, " Whiffles: 1000"); 
//  mvprintw(txt_y,txt_x, " Energy: 68"); 
//  wrefresh(menu);

//  
//  move(nlines/2,ncols/2);
//  refresh();


//    map.edit_map(nlines,ncols,viewport);
//    map.save_map();

    endwin();
    return 0;
}
