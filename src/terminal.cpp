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

	//setup colors
	init_pair(1, COLOR_BLACK, COLOR_YELLOW);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_BLACK, COLOR_WHITE);
}

void Terminal::write(std::string s) {
	addstr(s.c_str());
}

void Terminal::clear(int y) {
	move(0, y); //goto start of line
	write(std::string(getx(), ' ')); //fill line with white space
	move(0, y); //go back to start of line
}

void Terminal::zero(int y, std::string s) {
	clear(y);
	write(s);
}

void Terminal::update() {
	getmaxyx(window, y, x);
}

void Terminal::move(int x, int y) {
	wmove(window, y, x); //x and y are flipped to make it easier to manage
}

int Terminal::getx() {
	return x;
}

int Terminal::gety() {
	return y;
}