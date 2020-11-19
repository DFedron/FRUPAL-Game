# Project-Frupal
## Group 7 (authors):
 - Chiharu Akiyama
 - Huidong Wang
 - Austin Anderson
 - Anthony Pham
 - Camilo Schaser-Hughes
 
**November 10, 2020**
 
## Instructions:
 1. make with `make`
 2. run with `./frupal`
 3. currently arrow keys to explore `q` to quit.  that's it.
 4. a couple swamps around start
 5. river with bridge to south, wall to north
 6. meadows everywhere else, but feel free to walk about
 
## Version:
 This branch version has tiles colored black until you discover them.  It has implementation of a load file that is somewhat reproducable to create a 128x128 map.  It has hero produced on a dynamic viewport over a terrain input from input files.  It has a scroll mechanism.  All color is correctly displayed.  SWAMPS cost 2 energy, MEADOWS 1, WALLS and WATER cost 1 and send you back to your old position, as does trying to walk off the map.  You do not die currently, energy just goes to negative numbers.  Have testing x, y coordinates of hero by whiffles and energy.  It does not have a grovnick class.  With this implementation is just a struct.

## Load files:
 The load mechanism is built off of Chiharu's load mechanism. It is modified however to be able to create instance of terrain structures.  Any new file created needs to be linked inside of `terrain.txt`.  The `NUMTERRAIN` definition also needs to be changed in map.h.  The input structure is `int terrain;int y coord; int x coord`. y and x start from the top and left, respective to the map and controls.  After that you can type notes on the rest of the line to describe what you are making.
 Numbers asigned to terrain as follows:
  1. MEADOW is 1, if you want to overlay terrains.
  2. SWAMP is 2
  3. WATER is 3
  4. WALL is 4
  
 It initially sets everything to MEADOW, before loading in inputfiles.
