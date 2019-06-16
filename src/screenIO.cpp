#include <cmath>

#include "screen.hpp"
#include "keys.hpp"

//This file contains sections related to file and user IO

void Screen::pause() {
	getch();
}

void Screen::parseKey(int c) {
	if (key::del(c)) { //convert delete into a backspace
		currx++; //move over as if it was a backspace

		if (currx>file->linesize(curry)) {
			if (file->lines()>1) {
				setxy(0, curry+1);
			}
			else return;
		}
		parseKey(KEY_BACKSPACE);
		return;
	}
	else if (key::up(c)) {
		delta(0, -1);
	}
	else if (key::down(c)) {
		delta(0, 1);
	}
	else if (key::left(c)) {
		//left was pressed while at the start of a line
		if (currx==0&&curry>0) setxy(file->linesize(curry-1), curry-1);

		//left was pressed somewhere else
		else delta(-1, 0);
	}
	else if (key::right(c)) {
		//right was pressed at the end of a line
		if (currx==(int)file->linesize(curry)&&curry<file->lines()) setxy(0, curry+1);

		//right was pressed somewhere else
		else delta(1, 0);
	}
	else if (key::end(c)) {
		setxy(file->linesize(curry), curry);
	}
	else if (key::home(c)) {
		setxy(0, curry);
	}
	else if (key::enter(c)) {
		file->newline(currx, curry);
		setxy(0, curry+1);

		//update ruler to account for newlines
		ruler=std::log10(file->lines())+1;
	}
	//backspace is pressed at the start of a line
	else if (key::backspace(c)&&currx==0&&curry!=0) {
		int tempx=file->linesize(curry-1);

		file->delline(curry);
		setxy(tempx, curry-1);

		ruler=std::log10(file->lines())+1;
	}
	else {
		int tmpx=currx;

		setxy(0, curry);
		term->write(file->insert(c, tmpx, curry));

		if (key::backspace(c)) setxy(tmpx-1, curry);
		else setxy(tmpx+1, curry);
	}
}

void Screen::parseKeys(std::vector<int> c) {
	for (auto i:c) {
		parseKey(i);
	}
}

void Screen::useBuffer(std::shared_ptr<File> f) {
	file=f;
	ruler=std::log10(file->lines())+1;
}

std::string Screen::getfn() {
	return file->getfn();
}