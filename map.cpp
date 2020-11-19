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

////////////////////////////////////////////////////////////////////////////////
/*
    Our default constructors.  Normal default constructor deleted. The first
    Map constructor doesn't get used except for testing.
*/
////////////////////////////////////////////////////////////////////////////////

// used for testing just sets entire map to unviewed itemless meadow
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

// Our default constructor
Map::Map(WINDOW * vp, WINDOW * gm, char * inputfile) {

  viewport = vp; // sets viewport for easy access
  gamemenu = gm; // sets gamemenu for easy access

  // initally sets to unviewed, itemless MEADOW
  for(int i = 0; i < KSIZE; ++i)
    for(int j = 0; j < KSIZE; ++j) {
      frupal[i][j].square = MEADOW;
      frupal[i][j].viewed = false; // true total map, false for view
      frupal[i][j].feature = NULL; 
    }

  load_map(inputfile);

}

////////////////////////////////////////////////////////////////////////////////
/*
    Loading functions, first function loads file based on string.  loads that
    into a string array.  That array is filled with other files with drawings
    for the map.  Those files are loaded in in the load_terrain function.
*/
////////////////////////////////////////////////////////////////////////////////

void Map::load_map(string file) {

  ifstream infile;
  infile.open(file);
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

  if(!infile) { // error handling
    printw("Cannot open file.");
    exit(1);
  }

  // sample input: terrain#, yval, xval
  while(!infile.eof()) {
    infile >> temp_terrain; // loads in first num = enum type
    infile.get();
    infile >> i;  // gets the yvalue of grovnick
    infile.get();
    infile >> j;  // gets the xvalue of grovnick
    infile.ignore(100, '\n');
      // this converts the number to the matching enum terrain type
    frupal[i][j].square = static_cast<terrain>(temp_terrain);
  }
  infile.close();
}

////////////////////////////////////////////////////////////////////////////////
/*
    Display functions.  update_display takes in the y, x shift and prints the
    map according to the shift.  uses enum type conversion to int to match
    the COLOR_PAIR functions described in main.cpp 1-MEADOW, 2-SWAMP, 3-WATER
    4-WALL, 5-UNSEEN.
*/
////////////////////////////////////////////////////////////////////////////////

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
        mvwaddch(viewport, i - starty, j - startx, ' '); // prints grovnick tile
      }
      wattroff(viewport, COLOR_PAIR(color));

    }

}

////////////////////////////////////////////////////////////////////////////////
/*  
    Computational functions, helper functions, etc.
*/
////////////////////////////////////////////////////////////////////////////////

// ret -1 if off map, wall, or water, 2-swamp, 1-meadow
int Map::energy_cost(int y, int x) {
  
  // first checks if off grid, then checks grovnick enum type
  if(y < 0 || x < 0 || y >= KSIZE || x >= KSIZE)
    return -1;
  else if(frupal[y][x].square == MEADOW)
    return 1;
  else if(frupal[y][x].square == SWAMP)
    return 2;
  else if(frupal[y][x].square == WALL || frupal[y][x].square == WATER)
    return -1;

  return 0; // this should never happen though.
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


