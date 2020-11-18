#include "map.h"
#include <iostream>
#include <string>
#include <ncurses.h>
#include <fstream>

using namespace std;


//--- INITIALIZES MAP TO MEADOW GROVNICKS ---//

Map::Map(){
     map_size = 40;
   
     ifstream infile;
     infile.open("terrain.txt");
     if(!infile)
     {   printw("Cannot open file.");
        exit(1);
     }
     int i = 0;
     while(!infile.eof()){
         
          infile>>terrain_list[i];
          infile.ignore(100, '\n'); 
          i++;
     }
     infile.close();

    for(int i = 0;i < map_size; i++){
      for(int j = 0;j < map_size; j++){
          map[i][j].input_terrain(COLOR_PAIR(1),1);
      }
    }
   input_color_value();
}

// -- INPUTS COLOR_PAIR VALUE TO LIST --//
void Map::input_color_value(){
   for(int i = 0; i < terrain_num; i++)
        color_value_list[i] = COLOR_PAIR(i+2);   
 
}
void Map::load_map(){  

     for(int i = 0;i< terrain_num; i++) {
       int energy_cost = 1;
       if(terrain_list[i] == "swamp.txt" )
           energy_cost = 2; 
        load_terrain(terrain_list[i],color_value_list[i],energy_cost);
     }

}
void Map::load_terrain(string file, int color_value,int e_cost){
     int MAX = 100;
     int x, y = 0;

     ifstream infile;
     infile.open(file);

     if(!infile)
     {   printw("Cannot open file.");
        exit(1);
     }
     while(!infile.eof()){
          infile>>y;
          infile.get();
          infile.clear();
          infile>>x;
          infile.ignore(MAX, '\n'); 
          map[y][x].input_terrain(color_value,e_cost); 
     }
     infile.close();
}
void Map::print_map(){

    for(int i = 0;i<map_size;i++){
       for(int j = 0;j < map_size; j++){
           attron(map[i][j].get_terrain_color_value()); 
           map[i][j].print();
           attroff(map[i][j].get_terrain_color_value()); 
      }
      printw("\n");
    }
}
 void Map::print_grovnick(int i, int j){
   map[i][j].print();
}

bool Map::colors_match(int i, int j, int pair){
   if(map[i][j].get_terrain_color_value() == pair)
       return true;
   else 
      return false;
}


void Map::edit_map(int lines, int cols,WINDOW * viewport){

//--  CURSOR STARTING POSITION --//
   int row = lines/3;
   int col = cols/3;
 
   char c = 'p';
   int input = 0;

    keypad(viewport, TRUE); 

    while(1){
       if(c == 'p'){ 
          input = wgetch(viewport);
       
          switch(input)
          {
             case KEY_UP:
                  if(row != 0)
                     move(--row,col);
                  print_grovnick(row,col);
                     move(row,col); 
                  break;
             case KEY_DOWN:
                  if(row < map_size-1)
                       move(++row,col);
                  print_grovnick(row,col);
                     move(row,col); 
                  break;
            case KEY_LEFT:
                  if(col != 0)
                       move(row,--col);
                  print_grovnick(row,col);
                     move(row,col); 
                  break;
            case KEY_RIGHT:
                  if(col < map_size-1)
                       move(row,++col);
                  print_grovnick(row,col);
                     move(row,col); 
                  break;
            case 'm':
                  edit_terrain(row,col,COLOR_PAIR(1));
                  move(row,col);
                  break;
            case 's':
                  edit_terrain(row,col,COLOR_PAIR(2));
                  move(row,col);
                  break;                          
            case 'w':
                  edit_terrain(row,col,COLOR_PAIR(3));
                  move(row,col);
                  break;                          
            case 'l':
                  edit_terrain(row,col,COLOR_PAIR(4));
                  move(row,col);
                  break;                          
            case 'q':
                  c = 'q';
                  break;
            case 't':
                  printw("T");
                  break;
            case 'f':
                  printw("F");
                  break;
            default:
                  break;
        }  //end switch
          refresh();
      }   //end c == p
      else if(c == 'q')
        break;
      else
        break;
    } //end while loop
}

//--CHANGES GROVNICK TERRAIN DATA --//

void Map::edit_terrain(int i, int j, int color_pair_value){

    if(color_pair_value == COLOR_PAIR(3))  /* IF WATER TERRAIN */
        map[i][j].input_terrain(color_pair_value,2);
    else
       map[i][j].input_terrain(color_pair_value,1);
    
    print_grovnick(i,j);
}


void Map::save_map(){

       ofstream outfile;

       for(int n = 0; n < terrain_num; n++){ 
     
          outfile.open(terrain_list[n]);
          
          for(int i = 0; i < map_size;i++){
            for(int j = 0; j < map_size;j++){
               if(colors_match(i,j,COLOR_PAIR(n+2))){
               outfile << i;
               outfile << ";";
               outfile << j;
               outfile << "\n";
               }
            } 
          }
          outfile.close();
       }
}

