#include <string>
#include <cmath>

#include "screen.hpp"

Screen::Screen() {
	setlocale(LC_ALL, ""); //allow for unicode
	window=initscr(); //init and clear screen
	keypad(window, true); //allows arrow keys to be detected
	noecho(); //dont print characters to screen
	refresh();

	update();
}

void Screen::update() {
	getmaxyx(window, termy, termx);
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

void Screen::listen() {
	int c=getch();

	if (c==KEY_LEFT) { delta(-1, 0); }
	else if (c==KEY_RIGHT) { delta(1, 0); }
	else if (c==KEY_DOWN) { delta(0, 1); }
	else if (c==KEY_UP) { delta(0, -1); }
}

void Screen::home() {
	setxy(0, 0);
}

void Screen::setxy(int x, int y) {
	//make sure cursor stays within bounds
	if (
		x<0||
		x>=(termx-ruler-3)||
		x>((int)file->line(curry).length())||
		y<0||
		y>termy||
		y>=file->lines()
	) return;

	currx=x; //update current position
	curry=y; //
	wmove(window, y, x+ruler+3);
}

void Screen::delta(int dx, int dy) {
	setxy(dx+currx, dy+curry);
}

void Screen::render() {
	for (int i=0;i<file->lines();i++) {
		write(
			std::string(ruler-(int)(std::log10(i+1)+1), ' ')+ //calculate left spacing
			std::to_string(i+1)+" "+ //print line number
			"│ "+
			file->line(i)+ //display line buffer
			"\n"
		);
	}
}

void Screen::useBuffer(File* f) {
	file=f;
	ruler=std::log10(file->lines()+1)+1;
}