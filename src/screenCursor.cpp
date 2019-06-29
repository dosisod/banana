#include "screen.hpp"

//This file contains sections related to cursor movement/checking

void Screen::home() {
	setxy(0, 0);
}

void Screen::setxy(int x, int y) {
	if (y==-1&&filey>0) {
		filey--;
		return;
	}
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
	return charOver(0, 0);
}

char Screen::charOver(int x, int y) {
	if ((curry+y)>=0&&(curry+y)<file->lines()) {
		int decoded=file->decode(currx+x, curry+y);

		if ((decoded)>=0&&(decoded)<file->linesize(curry+y)) {
			//cursor pos is OK

			return file->rawLine(curry+y)[decoded];
		}
		return 0;
	}
	return 0;
}