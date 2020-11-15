//main.cpp

#include "item_tiles.h"
#include <iostream>
using namespace std;

// ***************************
// Currently just a skeleton,
// mainly just to see if the
// files compile at all
// ***************************


int main() {
    initscr();
    cbreak();
    noecho();

    printw("Hello World");
    refresh();

    getch();
    endwin();
    return 0;
}
