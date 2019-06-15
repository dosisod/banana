#include <string>

#include "terminal.hpp"

void Terminal::write(std::string s) {
	addstr(s.c_str());
}

void Terminal::update() {
	getmaxyx(window, y, x);
}

void Terminal::move(int x, int y) {
	wmove(window, y, x);
}