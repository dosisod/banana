#include <string>

#include "terminal.hpp"

Terminal::Terminal() {
	setlocale(LC_ALL, ""); //allow for unicode
	window=initscr(); //init and clear screen
	start_color();
	noecho(); //dont print characters to screen

	keypad(window, true); //allows arrow keys to be detected
	ESCDELAY=0;

	update();
}

void Terminal::write(std::string s) {
	addstr(s.c_str());
}

void Terminal::update() {
	getmaxyx(window, y, x);
}

void Terminal::move(int x, int y) {
	wmove(window, y, x); //x and y are flipped to make it easier to manage
}