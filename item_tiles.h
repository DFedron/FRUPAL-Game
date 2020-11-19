/*
 File name: item_tiles.h
 Author: Austin Anderson
 Group #7
 Version: 0.2
 */


#ifndef ITEMS_H
#define ITEMS_H

#include <ncurses.h>
//Needed for the binoculars
#include "hero.h"
//Needed for placement
#include "map.h"

//Abstract Item base class
class item{
	public:
        item();
        ~item();

		void display_info();
		virtual void remove() = 0;
};

//Derived clue class
class clue : public item{
	public:
        clue();
        ~clue();

        void random_clue(); //display some random clue
	private:
		//I don't think this needs to be here, but I am leaving it in as to not break anything
		//-Austin Anderson
	    bool true_false; //determine if the clue is true or false? 	
};

//Derived tool class
class tool : public item{
	public:
        tool(int cost);
        ~tool();

		//Derived from base class
		void display_info();
		int remove_whiffles(int w_rmv);
	private:
		//Potentially no longer needed, but also not removing to not break things
		//-Austin Anderson
		int tool_cost;
};

//Derived food class
class food : public item{
	public:
        food(int cost, int energy);
        ~food();

		void display_info();
		int add_energy(Hero * hero);
		int remove_whiffles(Hero * hero);

	private:
		int food_cost;
		int energy_value;
};

//Derived obstacle class
class obstacle : public item{
	public:
        obstacle(int movement_cost);
        ~obstacle();

		void display_info();
		int remove_energy(Hero * hero);

	private:
		int e_cost;
};

//Derived treasure chest class
class treasure_chest : public item{
	public:
        treasure_chest(int value);
        ~treasure_chest();

		void display_info();
		int add_whiffles(Hero * hero);

	private:
		int w_value;
};

//Derived ship class
class ship : public item{
	public:
        ship(int cost);
        ~ship();

		void display_info();
		int remove_whiffles(int w_rmv);

	private:
		int w_cost;
};

//Derived binocular class
class binoculars : public item{
	public:
        binoculars();
        ~binoculars();

		void display_info();
		int add_vision(Hero * hero);
};

#endif
