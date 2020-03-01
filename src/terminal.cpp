#include <string>

#include "terminal.hpp"

Terminal::Terminal() {
	//allow for unicode
	setlocale(LC_ALL, "");

	//init and clear screen
	window=initscr();
	start_color();

	//dont print characters to screen
	noecho();

	//allows arrow keys to be detected
	keypad(window, true);
	ESCDELAY=0;

	update();

	//setup colors
	init_pair(1, COLOR_BLACK, COLOR_YELLOW);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_BLACK, COLOR_WHITE);
}

void Terminal::write(std::string s) const {
	addstr(s.c_str());
}

void Terminal::clear(int y) const {
	//goto start of line
	move(0, y);

	//fill line with white space
	write(std::string(getx(), ' '));

	move(0, y);
}

void Terminal::zero(int y, std::string str) const {
	clear(y);
	write(str);
}

void Terminal::update() {
	getmaxyx(window, y, x);
}

void Terminal::move(int x, int y) const {
	wmove(window, y, x);
}

int Terminal::getx() const{
	return x;
}

int Terminal::gety() const {
	return y;
}