#include <string>

#include "screen.hpp"

Screen::Screen() {
	window=initscr();
	noecho();
	refresh();
}

Screen::~Screen() {
	endwin();
}

void Screen::write(std::string s) {
	printw(s.c_str());
}

void Screen::pause() {
	getch();
}