/* potential rewrite of Map class
   I just want to see a working model up 
   on our github, so we'll see if this sticks
   November 17, 2020
*/

#include <ncurses.h>
#include "map.h"

Map::Map(WINDOW * vp, WINDOW * gm) {

  viewport = vp;
  gamemenu = gm;

  for(int i = 0; i < KSIZE; ++i)
    for(int j = 0; j < KSIZE; ++j) {
      frupal[i][j].square = MEADOW;
      frupal[i][j].viewed = true; // true for testing, false later
      frupal[i][j].feature = NULL;
    }

  init_pair(1,COLOR_BLACK,COLOR_GREEN); //meadow
  init_pair(2,COLOR_BLACK,COLOR_MAGENTA); //swamp
  init_pair(3,COLOR_BLACK,COLOR_BLUE); //water
  init_pair(4,COLOR_BLACK,COLOR_WHITE);  //walls
  init_pair(5,COLOR_WHITE,COLOR_CYAN); //Royal Diamond
}

void Map::update_display() {

  int i, j, color, rows, cols;
  getmaxyx(viewport, rows, cols);

  for(i = 0; i < rows && i < KSIZE; ++i)
    for(j = 0; i < cols && j < KSIZE; ++j) {
      // this converts enum type to int match to color pair
      if(frupal[i][j].viewed)
        color = frupal[i][j].square;
      else
        color = UNSEEN;

      wattron(viewport, COLOR_PAIR(color));
      if(frupal[i][j].feature) {
        // TODO add in something to print out feature tiles
      }
      else {
        mvwaddch(viewport, i, j, ' ');
      }
      wattroff(viewport, COLOR_PAIR(color));

    }

}
