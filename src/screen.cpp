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
}

Screen::~Screen() {
	endwin();
}