#include "grovnick.h"
#include <iostream>
#include <string>
#include <ncurses.h>
#include <fstream>

using namespace std;


/***GROVNICK IMPLEMENTATION ***/

Grovnick::Grovnick(){
   color_value = 0;
   energy_cost = 0;

}
void Grovnick::input_terrain(int c_value,int e_cost)
{
    color_value = c_value;
    energy_cost = e_cost;
}
int Grovnick::get_terrain_energy_cost()
{
   return energy_cost; 
}
void Grovnick::print()
{
   start_color();  
   attron(color_value);
      printw(" ");
//    item.print();
   attroff(color_value);
}
int Grovnick::get_terrain_color_value()
{
   return color_value; 
}
