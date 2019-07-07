#include "screen.hpp"

//This file contains sections related to cursor movement/checking

void Screen::home() {
	setxy(0, 0);
}

void Screen::setxy(int x, int y) {
	int diffx=x-currx;
	int diffy=y-curry;
	//cursor is above screen, move file offset up

	if (y<0) {
		if (filey<=0) {
			curry=0;
		}
		else if (filey>-diffy) {
			filey+=diffy;
		}
		else {
			filey=0;
			curry=0;
		}
		return;
	}

	//if cursor is below the screen, move file offset down
	if (y==term->gety()&&realy()<file->lines()) {
		if (realy()+1<file->lines()) filey++;
		return;
	}

	//must be checked first or file->line(-1) could happen
	if (y<0||y>=file->lines()) return;

	//prevents cursor getting stuck when going to a shorter line
	if (x>(file->linesize(y+filey))) {
		x=file->linesize(y+filey);
	}

	//make sure cursor stays within bounds
	if (
		x<0||
		x>=(term->getx()-ruler-3)||
		y>=term->gety()
	) return;

	currx=x; //update current position
	curry=y; //
	term->move(x+ruler+1, y);
}

void Screen::delta(int dx, int dy) {
	setxy(dx+currx, dy+curry);
}

char Screen::charCurrent() {
	return charOver(0, 0);
}

char Screen::charAt(int x, int y) {
	return file->rawLine(y)[decode(x, y)];
}

char Screen::charOver(int x, int y) {
	x--; //cursor is over one relative to string pos
	if (realy()+y>=0&&realy()+y<file->lines()) {
		int decoded=decode(currx+x, realy()+y);

		if (decoded>=0&&decoded<file->linesize(realy()+y)) {
			//cursor pos is OK
			return charAt(currx+x, realy()+y);
		}
		return 0;
	}
	return 0;
}

int Screen::realy() {
	return curry+filey;
}