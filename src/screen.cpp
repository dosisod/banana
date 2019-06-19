#include <vector>
#include <string>

#include "commander.hpp"
#include "command.hpp"
#include "screen.hpp"
#include "keys.hpp"

//This file contains constructor, destructor, and super mode functions

Screen::Screen(std::shared_ptr<Terminal> t, int tab) {
	term=t; //pass terminal set from main so it can be used
	tabsize=tab;

	refresh();

	//setup colors
	init_pair(1, COLOR_BLACK, COLOR_YELLOW);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_BLACK, COLOR_WHITE);
}

Screen::~Screen() {
	endwin();
}