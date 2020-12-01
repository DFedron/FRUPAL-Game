/*  This is a potential design for the Hero class
    being designed for the frupal project
    cs300 Group 7
    November 16, 2020
*/

#include <ncurses.h>
#include <string.h>

#include "hero.h"
#include "map.h"

// our 'defaul constructor'
Hero::Hero(WINDOW *vp, WINDOW *gm) {

  xpos = 15;
  ypos = 15;
  whiffles = 1000;
  energy = 100;
  binoculars = false;
  ship = false;
  diamond = false;

  gamemenu = gm;
  viewport = vp;

  // creates map from input file folder
  char loadfile[] = "inputfiles/terrain.txt";
  map = new Map(viewport, gamemenu, loadfile); // implementation in map.h/cpp

  tool_belt = NULL; // empty tool belt
  curr_item = NULL; // empty curr_item(to be passed up from map)

  //tool_win pad
  tool_num = 0; //number of tools in toolbelt
  tool_row = 0;   
  tw_lr_row = 43;  //tool_win lower-right row
  tool_win = newpad(20, COLS-(KSIZE+2));
  prefresh(tool_win,tool_row,0,40,KSIZE+2,tw_lr_row,COLS);
}

// Hero::Hero(WINDOW * vp, WINDOW * gm, char * filename) {
//
//}

////////////////////////////////////////////////////////////////////////////////
/*
    These are our display functions.  scroll_function centers hero in map, and
    makes sure viewport doesn't go out of bounds. update_gamemenu prints the
    standard game menu. update_hero prints the hero with scroll mechanism
*/
////////////////////////////////////////////////////////////////////////////////

// updates display, kind of a wrapper function
void Hero::update_display() {

  int starty, startx; // will be modified in scroll_function

  werase(viewport); // resets viewport
  // changes starty, startx to center hero/map
  scroll_function(starty, startx);

  map->look_around(ypos, xpos, binoculars); // updates map to new view

  map->update_display(starty, startx); // prints map based off scroll shift #s
  update_hero(starty, startx);         // prints hero based off scroll shift #s

  update_gamemenu(); // erases and reprints gamemenu

  wrefresh(viewport); // refreshes viewport
  wrefresh(gamemenu); // refreshes game menu
  display_tool_window();
}

// returns true if dead, false otherwise
bool Hero::check_energy() {
  if (energy < 1)
    return true;
  else
    return false;
}

void Hero::add_energy(int en) { energy += en; }

// just erases and redraws the basic gamemenu
void Hero::update_gamemenu() {

  int rows, cols;
  getmaxyx(gamemenu, rows, cols);

  werase(gamemenu);
  wborder(gamemenu, '#', 0, ' ', ' ', '#', 0, '#', 0);

  map->print_options(gamemenu,ypos,xpos,ship); //prints player movement options
    

  // XXX remove these 3 lines, all testing stuff
  mvwprintw(gamemenu, rows - 6, 2, "This is for testing:");
  mvwprintw(gamemenu, rows - 5, 2, "x-position: %d", xpos);
  mvwprintw(gamemenu, rows - 4, 2, "y-position: %d", ypos);

  mvwprintw(gamemenu, 1, 1, "Menu:");
  mvwprintw(gamemenu, rows - 3, 2, "Energy: %d", energy);
  mvwprintw(gamemenu, rows - 2, 2, "Whiffles: %d", whiffles);
  wrefresh(gamemenu);
  display_tool_window(); 
}

// places the hero on the viewport, shifts by starty and startx
// which are measured with scroll function, puting hero in center
// or bound by 0 or KSIZE in map.
void Hero::update_hero(int starty, int startx) {

  wattron(viewport, COLOR_PAIR(6));
  mvwaddch(viewport, ypos - starty, xpos - startx, '@');
  wattroff(viewport, COLOR_PAIR(6));
}

// THIS IS THE START OF A COMPLICATED SCROLLING FUNCTION
// it's not that complicated but worth taking a look
void Hero::scroll_function(int &starty, int &startx) {

  int centerx, endx, centery, endy, rows, cols;

  getmaxyx(viewport, rows, cols); // find center of viewport
  centery = rows / 2;
  centerx = cols / 2;

  // finds beg and end of x-axis of viewport
  startx = xpos - centerx;
  endx = xpos + centerx;

  // makes sure we don't go out of bounds
  if (cols >= KSIZE)
    startx = 0;
  else if (startx < 0)
    startx = 0;
  else if (endx > KSIZE)
    startx = KSIZE - cols;

  // finds beg and end of y-axis of viewport
  starty = ypos - centery;
  endy = ypos + centery;

  // makes sure we don't go out of bounds
  if (rows >= KSIZE)
    starty = 0;
  else if (starty < 0)
    starty = 0;
  else if (endy > KSIZE) {
    starty = KSIZE - rows;
  }
  // END OF SCROLLING MECHANISM
}

////////////////////////////////////////////////////////////////////////////////
/*  updates hero pos.  if map->energy_cost(y,x) -1, it is WATER or WALL so
    resets position and costs 1 energy, otherwise drops down energy_cost
    1 for MEADOW, 2 for SWAMP.  updates display reprints entire screen with
    new positions.
*/
////////////////////////////////////////////////////////////////////////////////

void Hero::move_up() {
  int cost;

  --ypos;
  if ((cost = map->energy_cost(ypos, xpos, ship)) == -1) {
    ++ypos;
    --energy;

  } else
    energy -= cost;

  update_display();

  if (map->has_item(ypos, xpos)) {
    map->print_item(gamemenu, ypos, xpos);
    engage_item(ypos, xpos);
  }
  else{
     map->print_current_grovnick(gamemenu,ypos,xpos);
     wrefresh(gamemenu);
  }
  display_tool_window(); 
  
}

void Hero::move_down() {
  int cost;

  ++ypos;
  if ((cost = map->energy_cost(ypos, xpos, ship)) == -1) {
    --ypos;
    --energy;
  } else
    energy -= cost;

  update_display();

  if (map->has_item(ypos, xpos)) {
    map->print_item(gamemenu, ypos, xpos);
    engage_item(ypos, xpos);
  }
  else{
     map->print_current_grovnick(gamemenu,ypos,xpos);
     wrefresh(gamemenu);
  }
  display_tool_window(); 
}

void Hero::move_left() {
  int cost;

  --xpos;
  if ((cost = map->energy_cost(ypos, xpos, ship)) == -1) {
    ++xpos;
    --energy;
  } else
    energy -= cost;

  update_display();

  if (map->has_item(ypos, xpos)) {
    map->print_item(gamemenu, ypos, xpos);
    engage_item(ypos, xpos);
  }
  else{
     map->print_current_grovnick(gamemenu,ypos,xpos);
     wrefresh(gamemenu);
  }
  display_tool_window(); 
}

void Hero::move_right() {
  int cost;

  ++xpos;
  if ((cost = map->energy_cost(ypos, xpos, ship)) == -1) {
    --xpos;
    --energy;
  } else
    energy -= cost;

  update_display();

  if (map->has_item(ypos, xpos)) {
    map->print_item(gamemenu, ypos, xpos);
    engage_item(ypos, xpos);
    //       engage_item(map->frupal[ypos][xpos]->feature);
  }
  else{
     map->print_current_grovnick(gamemenu,ypos,xpos);
     wrefresh(gamemenu);
  }
  display_tool_window(); 
}

/// function for interacting with items
void Hero::engage_item(int ypos, int xpos) {

  // if food, tool, ship or binoculars, ask for purchase
  // if yes, subtract cost from account, add tool to belt, add ship somewhere,
  // binoculars is true, add energy to hero energy
  // after purchase, map removes item from map
  int ch; // will hold decisions
  // curr_item gets item
  map->get_item(curr_item, ypos, xpos);

  // downcasting all the pointers and just seeing what fits
  Food *food_ptr = dynamic_cast<Food *>(curr_item);
  Tool *tool_ptr = dynamic_cast<Tool *>(curr_item);
  Obstacle *ob_ptr = dynamic_cast<Obstacle *>(curr_item);
  Ship *ship_ptr = dynamic_cast<Ship *>(curr_item);
  Binoculars *bino_ptr = dynamic_cast<Binoculars *>(curr_item);
  Treasure_chest *treasure_ptr = dynamic_cast<Treasure_chest *>(curr_item);
  Diamond *diamond_ptr = dynamic_cast<Diamond *>(curr_item);

  nodelay(stdscr, false);
  // must find one of them at least
  if (food_ptr) {
    ch = getch();
    while(ch != 'y' && ch != 'n')
      ch = getch();
// makes decision if should buy the food or not.
    if(ch == 'y') {
      whiffles -= curr_item->get_cost();
      energy += curr_item->get_energy();
      map->remove_item(ypos, xpos);
      update_display();
      display_tool_window();
      mvwprintw(gamemenu, 5, 3, "Thanks for your purchase!");
      wrefresh(gamemenu);
      display_tool_window();
    }
    else {
      update_display();
      display_tool_window();
      mvwprintw(gamemenu, 5, 3, "Maybe next time!");
      wrefresh(gamemenu);
      display_tool_window();
    }
  } else if (tool_ptr) {
    ch = getch();
    while(ch != 'y' && ch != 'n'){
      ch = getch();
    }
// makes decision if should buy the tool or not.
    if(ch == 'y') {
        if (!tool_belt) 
        {
            tool_belt = new Tool(*tool_ptr);
        } 
        else 
        {
            Item *temp = new Tool(*tool_ptr);
            temp->get_next() = tool_belt;
            tool_belt = temp;
        }
        tool_num++;
        whiffles -= curr_item->get_cost();
        map->remove_item(ypos, xpos);
        update_display();
        mvwprintw(gamemenu, 5, 3, "Thanks for your purchase!");
        wrefresh(gamemenu);
        display_tool_window();
    }
    else
    {
        update_display();
        mvwprintw(gamemenu, 5, 3, "Maybe next time!");
        wrefresh(gamemenu);
        display_tool_window();
    }
        display_tool_window();
  } 
  else if (ob_ptr) {
    display_tool_window();
    if (tool_belt) {
        int r = 35;
        mvwprintw(gamemenu,r,3,"< Toolbelt >");  
        mvwprintw(gamemenu,r++,3," Choose a tool with the arrow keys. ");  
        mvwprintw(gamemenu,r++,3," Press 'Enter' to choose. Press 'e' to exit Toolbelt");  
        wrefresh(gamemenu);

        string ob_type;
        curr_item->get_name(ob_type); // gets type of obstacle
        if( choose_tool(ob_type)) // if no tool was chosen, remove energy..
            energy -= ob_ptr->get_energy();
    } else
        energy -= ob_ptr->get_energy();
      map->remove_item(ypos, xpos);
      wrefresh(gamemenu);
      display_tool_window();
       
  } else if (ship_ptr) {
    ch = getch();
    while(ch != 'y' && ch != 'n')
      ch = getch();
// makes decision if should buy the ship or not.
    if(ch == 'y') {
       ship = true;
       map->remove_item(ypos, xpos);
    }
  } else if (bino_ptr) {
    ch = getch();
    while(ch != 'y' && ch != 'n')
      ch = getch();
// makes decision if should buy the binoculars or not.
    if(ch == 'y') {
       binoculars = true;
       map->remove_item(ypos, xpos);
    }
  } else if (treasure_ptr) {
    ch = getch();

    while(ch != 10) // while it's not <ENTER>
      ch = getch();

    whiffles += treasure_ptr->get_whiffles();
    map->remove_item(ypos, xpos);
    update_display();
    wrefresh(gamemenu);
  }

  else if (diamond_ptr) {
    diamond = true;
    whiffles += diamond_ptr->get_whiffles();

    // maybe temporary, maybe move to main.cpp
    // for the same endgame,so most data from main end_game_menu function
    WINDOW *endgame;
    endgame = newwin(20, 50, (LINES - 20) / 2, (COLS - 50) / 2);
    int c = '#';
    wborder(endgame, c, c, c, c, c, c, c, c);

    mvwprintw(endgame, 9, 20, "YOU WIN!!!");

    wrefresh(endgame);
    getch();
    endwin();
    exit(0);
  }
  curr_item = NULL;
  display_tool_window();
//  map->remove_item(ypos, xpos);
}

bool Hero::tool_match(Item *&curr_tool, string ob_type,int choice_num) {
  if (!curr_tool)
    return false;
  string tool_ob_type;
  
   if(choice_num == 0){ //this is selected tool
         curr_tool->get_obstacle_type(tool_ob_type);

           //clears gamemenu lines
            wmove(gamemenu,20,3);
            wclrtoeol(gamemenu); 
            wmove(gamemenu,21,3);
            wclrtoeol(gamemenu); 
            wmove(gamemenu,22,3);
            wclrtoeol(gamemenu); 

         if (ob_type.compare(tool_ob_type) == 0) {
              float quotient = curr_item->get_energy() / tool_belt->get_energy();
              energy -= static_cast<int>(quotient);

             update_gamemenu();

            //Prints tool name used to remove obstacle
              string tool_name;
              curr_tool->get_name(tool_name);
              mvwprintw(gamemenu, 20, 3, "Removed ");
              waddstr(gamemenu, tool_ob_type.data());
              mvwprintw(gamemenu, 21, 3, "with ");
              waddstr(gamemenu, tool_name.data());
              wrefresh(gamemenu);

           // remove toolbelt item...
            if (!curr_tool->get_next()) // if there's no next tool in toolbelt
            {
                if(tool_belt == curr_tool)
                     tool_belt = NULL;
                delete curr_tool;
                curr_tool= NULL;
            } 
            else {
                Item *temp = curr_tool->get_next();
                if (curr_tool == tool_belt){
                      curr_tool = temp;
                      delete tool_belt;
                      tool_belt = temp;
                }
                else{
                      delete curr_tool;
                      curr_tool = temp;
                      temp = NULL;
                }
            }//ends remove  
            tool_num--;
            return true;
        }//ends compare 
        else {
            string tool_name;
            curr_tool->get_name(tool_name);
            mvwprintw(gamemenu, 20, 3, "Cannot remove ");
            waddstr(gamemenu, ob_type.data());
            mvwprintw(gamemenu, 21, 3, "with ");
            waddstr(gamemenu, tool_name.data());
            mvwprintw(gamemenu, 22, 3, "Choose a different tool ");
            wrefresh(gamemenu);
            return false;
       }
  } //ends choice
  else
    return tool_match(curr_tool->get_next(), ob_type,choice_num-1);
}
void Hero::print_tool_belt(Item *t_belt, int row, int choice_num,bool select) {
  if (!t_belt)
    return;
  string name;
//if number is zero, highlight that tool
  if(choice_num == 0 && select == TRUE)
    wattron(tool_win,A_REVERSE);   //turns on highlight

  t_belt->get_name(name);
  if(t_belt->get_energy() == 0)
      return;
  mvwprintw(tool_win,row++,3, " <> ");
  waddstr(tool_win,  name.data());
  wprintw(tool_win, ": Rating %dX", t_belt->get_energy());
 
  wattroff(tool_win,A_REVERSE);  //turns off hightlight

  print_tool_belt(t_belt->get_next(), row,choice_num-1,select);
}

///////////////////////////////////////////////////////////////
//Toolbelt is the window that displays all the tools
//The player can scroll through it to choose a tool for an obstacle
///////////////////////////////////////////////////////////////
void Hero::display_tool_window(){
    werase(tool_win);
//    wborder(tool_win,' ','-','-',' ',' ', ' ', ' ',' ');
    int row = 0;
    tool_row = 0;
    mvwprintw(gamemenu,39,3," < Toolbelt > ");  

    print_tool_belt(tool_belt,row,0,0);     

    prefresh(tool_win,tool_row,0,40,KSIZE+2,tw_lr_row,COLS);

}

//opens toolbelt for choosing tools
bool Hero::choose_tool(string ob_type){
    int row = 1;
    int choice_num = 0; // is the place number of the tool in the list
    char ch = 'c'; 
    bool select = TRUE;
    Item *curr_tool= tool_belt;
    keypad(tool_win,TRUE);
    tool_row = 1;  
    while(ch != 't' && ch != 'f'){

        print_tool_belt(curr_tool,row,choice_num,select);     
        prefresh(tool_win,tool_row,0,40,KSIZE+2,tw_lr_row,COLS);
        int input = wgetch(tool_win);

      switch(input){
           case KEY_DOWN:
               if((choice_num+1) < tool_num){   
                  choice_num++;     
                  print_tool_belt(tool_belt,row,choice_num,select);
               
                  if(tool_num > choice_num && tool_row < 20 && tool_row ){
                     prefresh(tool_win,tool_row++,0,40,KSIZE+2,tw_lr_row,COLS);
                  }
                  else
                     prefresh(tool_win,tool_row,0,40,KSIZE+2,tw_lr_row,COLS);
               }
               break;     
           case KEY_UP:
               if(choice_num != 0){
                  choice_num--;     
                  print_tool_belt(tool_belt,row,choice_num,select);
               
                  if(tool_row > 1){
                      prefresh(tool_win,tool_row--,0,40,KSIZE+2,tw_lr_row,COLS);
                  }
                  else
                      prefresh(tool_win,tool_row,0,40,KSIZE+2,tw_lr_row,COLS);
               }
               break;     
           case 10: //Enter
               if(tool_match(curr_tool,ob_type,choice_num)){
                 ch = 't'; 
                  choice_num = 0;
                    display_tool_window();                 
                    prefresh(tool_win,tool_row--,0,40,KSIZE+2,tw_lr_row,COLS);
               }else
               prefresh(tool_win,tool_row,0,40,KSIZE+2,tw_lr_row,COLS);
               break;
          case 'e':
               ch = 'f';
               break;
          default:
               break;
      }
   } 
   if(ch == 't')
      return true;
   return false;
}


////////////////////////////////////////////////////////////////////////////////
