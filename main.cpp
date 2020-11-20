//CS300 Fall Term 2020
//Group 7
//Kingdom of Frupal

#include "hero.h"
#include "map.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ncurses.h>
#include<cstdlib>
#define MENUWIDTH 35 // sets the menu width

using namespace std;

void start();
int main(int argc, char ** argv) 
{
  // TODO check for argc#, exit exception for > 2
  if(argc > 1){
  	cout << "please enter ./frupal\n";
  	return 0;  
  }
  
  
  initscr();
  // TODO check for screen size, error msg/exit out if
  // LINES < 24 or COLS < 80.
  if(LINES < 24 || COLS < 80){
  	cout << "Your screen is less than 80*24\n";
	return 0;
  }

  noecho();                 // doesn't print input char to screen
  keypad(stdscr, true);     // takes in the up/down/left/right
  nodelay(stdscr, true);    // immediately takes in chars from input
  curs_set(0);              // doesn't print cursor to screen

  start_color(); // colors are matched to enum #'s
  init_pair(1,COLOR_BLACK,COLOR_GREEN);   // MEADOW = 1
  init_pair(2,COLOR_BLACK,COLOR_MAGENTA); // SWAMP = 2
  init_pair(3,COLOR_BLACK,COLOR_BLUE);    // WATER = 3
  init_pair(4,COLOR_BLACK,COLOR_WHITE);   // WALLS = 4
  init_pair(5,COLOR_BLACK,COLOR_BLACK);   // UNSEEN = 5
  init_pair(6,COLOR_YELLOW,COLOR_RED);    // Hero
  init_pair(7,COLOR_WHITE,COLOR_CYAN);    // Royal Diamond

  //////////////////////////////////////////////////////////////////////////////
  // The primary control of game is move to the function below called start() //
  //////////////////////////////////////////////////////////////////////////////
  
  
  
  //This is start menu
  //Maybe add customized function?
	string option[2] = {"1.Start Game","0.Exit"};
	int hightlight = 0;
  	int choice;//get the input
  while (true)
  {	
  	WINDOW * mainMenu = newwin(7, COLS-16, LINES-13, 7);
	box(mainMenu,0,0);
	refresh();
	wrefresh(mainMenu);
	keypad(mainMenu, true);
	for(int i=0; i<2; ++i)
	{
		if(i == hightlight)
			wattron(mainMenu, A_REVERSE);
		//make sure it's on the center.
		//12 is length of the "1.Start Game"
		mvwprintw(mainMenu, i+1, (COLS-16-12)/2, option[i].c_str());
		wattroff(mainMenu, A_REVERSE);
	}		
		choice = wgetch(mainMenu);
		switch (choice)
	    	{
	      	case 10: //10 is the value of the key Enter
	      		if(hightlight == 0){
				clear();
	      			start();  //start the game
			}
	      		else if (hightlight == 1){
				endwin();
	      			return 0;
			}
	      		break;
		  	case KEY_UP:
	       	 	--hightlight;
	       	 	if(hightlight < 0)
	       	 		hightlight = 0;
	        	break;
	      	case KEY_DOWN:
	       	 	++hightlight;
	       	 	if(hightlight > 1)
	       	 		hightlight = 1;
	        	break;
	    	default:
	    		break;
	    	}
	    
	clear();
	refresh();
  }
    endwin(); // ends window functionality
    return 0;
   
}

void start()
{
  // TODO if argc == 2, create Hero(viewport, in_
  
  Hero * hero; // hero object
  WINDOW * viewport, * gamemenu; // our 2 windows
  // figures out what the height and width of menu/viewport is
  int gmheight, gmwidth = MENUWIDTH, vpheight, vpwidth;
  vpheight = LINES;
  gmheight = LINES;
  vpwidth = COLS - gmwidth;

  // changes menu width is screen is really big.
  if(vpwidth > KSIZE) {
    vpwidth = KSIZE;
    gmwidth = COLS - vpwidth;
  }

  viewport = newwin(vpheight, vpwidth, 0, 0); // sets location/height/width of viewport
  gamemenu = newwin(gmheight, gmwidth, 0, vpwidth + 1); // same with menu
  wborder(gamemenu, '#', 0, ' ', ' ', '#', 0, '#', 0); // should put just on left side
 
  hero = new Hero(viewport, gamemenu);
  int ch;
  refresh(); // starts the screen
  hero->update_display(); // prints the initial screen

  // this is the primary control of game.
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
    if(hero->check_energy()){
   // 	timeout(2000); //wait 2 second;
	break;
    }
    // TODO add in check for hero's energy
    // print 'you died' screen and exit
    // or option to go again?...
    // also need to make a get_hero_en() function in hero.cpp/h
  }
}
