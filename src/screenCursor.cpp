#include "screen.hpp"

//This file contains sections related to cursor movement/checking

void Screen::home() {
	setxy(0, 0);
}

void Screen::setxy(int x, int y) {
	//cursor is above screen, move file offset up
	if (y==-1&&filey>0) {
		filey--;
		return;
	}
	//if cursor is below the screen, move file offset down
	else if (y==term->gety()&&(curry+filey)<file->lines()) {
		if ((filey+curry+1)<file->lines()) filey++;
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
	return charOver(0, 0+filey);
}

char Screen::charAt(int x, int y) {
	return file->rawLine(y)[decode(x, y)];
}

char Screen::charOver(int x, int y) {
	x--; //cursor is over one relative to string pos
	if ((curry+y)>=0&&(curry+y)<file->lines()) {
		int decoded=decode(currx+x, curry+y);

		if ((decoded)>=0&&(decoded)<file->linesize(curry+y)) {
			//cursor pos is OK
			return charAt(currx+x, curry+y);
		}
		return 0;
	}
	return 0;
}