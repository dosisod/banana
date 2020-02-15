#include <vector>
#include <string>

#include "commander.hpp"
#include "command.hpp"
#include "screen.hpp"
#include "keys.hpp"

Screen::Screen(std::shared_ptr<Terminal> terminal, int tabsize) :
	terminal(terminal),
	tabsize(tabsize)
{
	refresh();
}

Screen::~Screen() {
	endwin();
}