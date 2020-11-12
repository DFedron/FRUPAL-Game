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
		void display_info();
		virtual void remove() = 0;
}
//Derived clue class
class clue : public item{
	public:
	private:
		
}
//Derived tool class
class tool : public item{
	public:
		//Derived from base class
		void display_info();
		int remove_whiffles(int w_rmv);
	private:
		int tool_cost;
}
//Derived food class
class food : public item{
	public:
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
		void display_info();
		int remove_energy(int e_rmv);
	private:
		int e_cost;
}
//Derived treasure chest class
/class treasure_chest : public item{
	public:
		void display_info();
		int add_whiffles(int w_added);
	private:
		int w_value;
}
//Derived ship class
class ship : public item{
	public:
		void display_item();
		int remove_whiffles(int w_rmv);
	private:
		int w_cost;
}
//Derived binocular class
class binoculars : public item{
	public:
		void display_info();
		int add_vision();
}

#endif
