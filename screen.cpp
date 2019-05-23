#include <string>
#include <cmath>

#include "screen.hpp"

Screen::Screen() {
	setlocale(LC_ALL, "");
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

void Screen::home() {
	setxy(0, 0);
}

void Screen::setxy(int x, int y) {
	wmove(window, x, y);
}

void Screen::render(File* f) {
	int ruler=std::log10(f->lines()+1)+1;

	for (int i=0;i<f->lines();i++) {
		write(
			std::string(ruler-(int)(std::log10(i+1)+1), ' ')+
			std::to_string(i+1)+" "+
			"│ "+
			f->line(i)+
			"\n"
		);
	}
}