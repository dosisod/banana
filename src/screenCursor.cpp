#include "screen.hpp"

void Screen::home() {
	setxy(0, 0);
}

void Screen::setxy(int x, int y) {
	int diffx=x - currx;
	int diffy=y - curry;

	if (y < 0) {
		//cursor is above screen, move file offset up

		if (filey <= 0) {
			//file offset is as far up as it can go
			curry=0;
		}
		else if (filey > -diffy) {
			//there is room to move the file offset up
			filey+=diffy;
		}
		else {
			//there is no room to move
			filey=0;
			curry=0;
		}
		return;
	}
	else if (y + filey >= file->lines()) {
		//couldnt move down but the botton line is visible in the terminal
		if (file->lines() - filey < terminal->gety()) {
			curry=file->lines() - filey - 1;
		}

		else {
			//the bottom of the file was reached, so move lastline to bottom of screen
			curry=terminal->gety() - 1;
			filey=file->lines() - terminal->gety();
		}
		return;
	}

	else if (
			filey + y < file->lines() &&
			y >= terminal->gety() &&
			file->lines() - filey >= terminal->gety()
		) {
		//cursor moved past bottom of screen but didnt hit last line, move file offset
		curry=terminal->gety() - 1;
		filey+=y - terminal->gety() + 1;

		return;
	}

	if (y < 0) {
		y=0;
	}
	else if (y >= file->lines()) {
		y=file->lines() - 1;
	}

	//prevents cursor getting stuck when going to a shorter line
	if (x > (file->linesize(y + filey))) {
		x=file->linesize(y + filey);
	}

	//make sure cursor stays within bounds
	if (
		x < 0 ||
		x >= (terminal->getx() - ruler - 3) ||
		y >= terminal->gety()
	) return;

	//update current position
	currx=x;
	curry=y;

	terminal->move(
		decode(x, realy()) + ruler + 1,
		y
	);
}

void Screen::delta(int dx, int dy) {
	setxy(dx + currx, dy + curry);
}

char Screen::charCurrent() {
	return charOver(0, 0);
}

char Screen::charAt(int x, int y) {
	return file->rawLine(y)[decode(x, y)];
}

char Screen::charOver(int x, int y) {
	x--;

	if (realy() + y >= 0 && realy() + y < file->lines()) {
		int decoded=decode(currx + x, realy() + y);

		if (decoded >= 0 && decoded < file->linesize(realy() + y)) {
			//cursor pos is OK
			return charAt(currx + x, realy() + y);
		}
		return 0;
	}
	return 0;
}

int Screen::realy() {
	return curry + filey;
}