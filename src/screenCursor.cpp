#include "screen.hpp"

//This file contains sections related to cursor movement/checking

void Screen::home() {
	setxy(0, 0);
}

void Screen::setxy(int x, int y) {
	//must be checked first or file->line(-1) could happen
	if (y<0||y>=file->lines()) return;

	//prevents cursor getting stuck when going to a shorter line
	if (x>(file->linesize(y))) {
		x=file->linesize(y);
	}

	//make sure cursor stays within bounds
	if (
		x<0||
		x>=(termx-ruler-3)||
		y>=termy
	) return;

	currx=x; //update current position
	curry=y; //
	wmove(window, y, x+ruler+1);
}

void Screen::delta(int dx, int dy) {
	setxy(dx+currx, dy+curry);
}