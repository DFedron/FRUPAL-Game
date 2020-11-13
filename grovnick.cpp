#include "grovnick.h"
#include <iostream>
#include <string>
#include <ncurses.h>
#include <fstream>

using namespace std;

/*** TERRAIN IMPLEMENTATION ***/

Terrain::Terrain()
{
   color_value = 0;
   energy_cost = 0;
}
void Terrain::input_terrain(int c_value,int e_cost)
{
    color_value = c_value;
    energy_cost = e_cost;
}
void Terrain::print_terrain()
{
      printw(" ");
}
int Terrain::get_energy_cost()
{
    return energy_cost;
}
int Terrain::get_color_value()
{
    return color_value;
}


/***GROVNICK IMPLEMENTATION ***/

Grovnick::Grovnick(){

}
void Grovnick::input_terrain(int c_value,int e_cost)
{
    terrain.input_terrain(c_value,e_cost);
}
int Grovnick::get_terrain_energy_cost()
{
   return terrain.get_energy_cost();
}
void Grovnick::print()
{
   terrain.print_terrain();
}
int Grovnick::get_terrain_color_value()
{
   return terrain.get_color_value();
}
