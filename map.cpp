/* potential rewrite of Map class
   I just want to see a working model up 
   on our github, so we'll see if this sticks
   November 17, 2020
*/

#include <ncurses.h>
#include <string>
#include <fstream>
#include "map.h"

using namespace std;

Map::Map(WINDOW * vp, WINDOW * gm) {

  viewport = vp;
  gamemenu = gm;

  for(int i = 0; i < KSIZE; ++i)
    for(int j = 0; j < KSIZE; ++j) {
      frupal[i][j].square = MEADOW;
      frupal[i][j].viewed = false; // true total map, false for view
      frupal[i][j].feature = NULL; 
    }
}

Map::Map(WINDOW * vp, WINDOW * gm, char * inputfile) {

  viewport = vp;
  gamemenu = gm;

  for(int i = 0; i < KSIZE; ++i)
    for(int j = 0; j < KSIZE; ++j) {
      frupal[i][j].square = MEADOW;
      frupal[i][j].viewed = false; // true total map, false for view
      frupal[i][j].feature = NULL; 
    }

    // TODO HERE implement Chiharu's infile

  ifstream infile;
  infile.open(inputfile);
  if(!infile) {
    printw("Cannot open file.");
    exit(1);
  }

  int i = 0;
  string terrain_list[NUMTERRAIN];

  while(!infile.eof()) {
    infile >> terrain_list[i];
    infile.ignore(100, '\n');
    ++i;
  }
  infile.close();

  for(i = 0; i < NUMTERRAIN; ++i)
    load_terrain(terrain_list[i]);
}

void Map::load_terrain(string file) {

  int i, j, temp_terrain;

  ifstream infile;
  infile.open(file);

  if(!infile) {
    printw("Cannot open file.");
    exit(1);
  }

  // sample input: terrain#, yval, xval
  while(!infile.eof()) {
    infile >> temp_terrain;
    infile.get();
    infile >> i; 
    infile.get();
    infile >> j;
    infile.ignore(100, '\n');

    frupal[i][j].square = static_cast<terrain>(temp_terrain);
  }
  infile.close();
}
// takes in hero's pos & binoculars, adjust map accordingly
void Map::look_around(int ypos, int xpos, bool binoculars) {

  int sight = 1;
  sight += binoculars;

  for(int i = ypos - sight; i <= ypos + sight; ++i)
    for(int j = xpos - sight; j <= xpos + sight; ++j) 
      if(i >= 0 && j >= 0 && i < KSIZE && j < KSIZE) // check if on map
        frupal[i][j].viewed = true;
}

void Map::update_display(int starty, int startx) {

  int i, j, color, rows, cols;
  getmaxyx(viewport, rows, cols);

  for(i = starty; i < starty + rows && i < KSIZE; ++i)
    for(j = startx; j < startx + cols && j < KSIZE; ++j) {
      // this converts enum type to int match to color pair
      if(frupal[i][j].viewed)
        color = frupal[i][j].square; // converts enum to #, matched in main
      else
        color = UNSEEN; // UNSEEN = 5 matches init_pair in main

      wattron(viewport, COLOR_PAIR(color));
      if(frupal[i][j].feature) {
        // TODO add in something to print out feature tiles
        // don't forget to adjust with the scroll: starty, startx
      }
      else {
        mvwaddch(viewport, i - starty, j - startx, ' ');
      }
      wattroff(viewport, COLOR_PAIR(color));

    }

}

// ret -1 if off map, wall, water, 2-swamp, 1-meadow
int Map::energy_cost(int y, int x) {
  
  // first checks if off grid, then checks gronick enum type
  if(y < 0 || x < 0 || y >= KSIZE || x >= KSIZE ||
    frupal[y][x].square == WALL || frupal[y][x].square == WATER)
    return -1;
  else if(frupal[y][x].square == MEADOW)
    return 1;
  else if(frupal[y][x].square == SWAMP)
    return 2;

  return 0; // this should never happen though.
}



