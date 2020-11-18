/*
 File name: item_tiles.cpp
 Author: Austin Anderson
 Group #7
 Version: 0.1
 */
#include "item_tiles.h"

/*
 * Item base class
 */

//Constructor
item::item(){}

//Destructor
item::~item(){}

/*
 * Clue Class
 */

//Constructor
clue::clue(){}

//Destructor
clue::~clue(){}

//Public Functions

void clue::random_clue(){
	//Stub
	//There will likely be an addition of random values to the header file call
	//Using a seeded value, the possibility of the correct clue can be set to
	//being reasonable to downright impossible to use.
	return;
}

/*
 * Tool Class
 */

//Constructor
tool::tool(int cost){
	tool_cost = cost;
}

//Deconstructor
tool::~tool(){}

//Public Functions

void tool::display_info(){
	//Stub
	return;
}

int tool::remove_whiffles(int w_rmv){
	//Stub
	return 0;
}

/*
 * Food Class
 */

//Constructor
food::food(int cost, int energy){
	food_cost = cost;
	energy_value = energy;
}

//Deconstructor
food::~food(){}

//Public Functions

void food::display_info(){
	//Stub
	return;
}

int food::add_energy(Hero * hero){
	//Stub
	//Takes the hero and adds energy to the hero's energy meter based on the
	//amount the food provides
	return 0;
}

int food::remove_whiffles(Hero * hero){
	//Stub
	//Removes whiffles for the hero's wallet based on the cost of the food
	//Need to ensure that the hero cannot buy the food if they doe not have
	//enough whiffles to purchase it. This goes for other purchases too
	return 0;
}

/*
 * Obstacle Class
 */

//Constructor
obstacle::obstacle(int movement_cost){}

//Deconstructor
obstacle::~obstacle(){}

//Public Functions

void obstacle::display_info(){
	//Stub
	return;
}

int obstacle::remove_energy(Hero * hero){
	//Stub
	//Call the hero's remove energy function, but do not update the position
	return 0;
}

/*
 * Treasure Chest Class
 */

//Constructor
treasure_chest::treasure_chest(int value){
	w_value = value;
}

//Deconstructor
treasure_chest::~treasure_chest(){}

//Public Functions

void treasure_chest::display_info(){
	//Stub
	return;
}

int treasure_chest::add_whiffles(Hero * hero){
	//Stub
	//Add the value of the treasure to the hero's wallet
	return 0;
}

/*
 * Ship Class
 */

//Constructor
ship::ship(int cost){
	w_cost = cost;
}

//Deconstructor
ship::~ship(){}

//Public Functions

void ship::display_info(){
	//Stub
	return;
}

int remove_whiffles(Hero * hero){
	//Stub
	//Remove whiffles from the hero's wallet
	return 0;
}

/*
 * Binocular Class
 */

//Constructor
binoculars::binoculars(){}

//Destructor
binoculars::~binoculars(){}

//Public Functions

void binoculars::display_info(){
	//Stub
	return;
}

int binoculars::add_vision(Hero * hero){
	//Stub
	//Requires the hero class function to alter the vision
	//*hero.add_vision();
	return 1;
}
