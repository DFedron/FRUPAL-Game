/*
 File name: item_tiles.h
 Author: Austin Anderson
 Group #7
 Version: 0.1
 */
#ifndef
#define

#include <ncurses>

//Abstract Item base class
class item{
	public:
        item();
        ~item();

		void display_info();
		virtual void remove() = 0;
}
//Derived clue class
class clue : public item{
	public:
        clue();
        ~clue();

        void random_clue(); //display some random clue
	private:
	    bool true_false; //determine if the clue is true or false? 	
}
//Derived tool class
class tool : public item{
	public:
        tool();
        ~tool();

		//Derived from base class
		void display_info();
		int remove_whiffles(int w_rmv);
	private:
		int tool_cost;
}
//Derived food class
class food : public item{
	public:
        food();
        ~food();

		void display_info();
		int add_energy(int e_added);
		int remove_whiffles(int w_rmv);

	private:
		int food_cost;
		int energy_value;
}
//Derived obstacle class
class obstacle : public item{
	public:
        obstacle();
        ~obstacle();

		void display_info();
		int remove_energy(int e_rmv);

	private:
		int e_cost;
}
//Derived treasure chest class
class treasure_chest : public item{
	public:
        treasure_chest();
        ~treasure_chest();

		void display_info();
		int add_whiffles(int w_added);

	private:
		int w_value;
}
//Derived ship class
class ship : public item{
	public:
        ship();
        ~ship();

		void display_item();
		int remove_whiffles(int w_rmv);

	private:
		int w_cost;
}
//Derived binocular class
class binoculars : public item{
	public:
        binoculars();
        ~binoculars();

		void display_info();
		int add_vision();
}

#endif
