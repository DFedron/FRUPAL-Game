#ifndef
#define

#include <ncurses>

//Abstract Item base class
class item{
	public:
		display_info() = 0;
		remove() = 0;
}
//Derived clue class
class clue : public item{

}

#endif
