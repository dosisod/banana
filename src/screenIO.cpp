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

	if (key::escape(c)) {
		super();
	}
	else if (!isSuper&&key::up(c)) {
		delta(0, -1);
	}
	else if (!isSuper&&key::down(c)) {
		delta(0, 1);
	}
	else if (key::left(c)) {
		if (isSuper) {
			//left was pressed while in super mode
			if (superx!=0) superx--;
		}
		else {
			//left was pressed while at the start of a line
			if (currx==0&&curry>0) setxy(file->linesize(curry-1), curry-1);

			//left was pressed somewhere else
			else delta(-1, 0);
		}
	}
	else if (key::right(c)) {
		if (isSuper) {
			//right was press while in super mode
			if (superx<superLine->size()) superx++;
		}
		else {
			//right was pressed at the end of a line
			if (currx==(int)file->linesize(curry)&&curry<file->lines()) setxy(0, curry+1);

			//right was pressed somewhere else
			else delta(1, 0);
		}
	}
	else if (key::end(c)) {
		if (isSuper) superx=superLine->size();
		else setxy(file->linesize(curry), curry);
	}
	else if (key::home(c)) {
		if (isSuper) superx=0;
		else setxy(0, curry);
	}
	else if (!isSuper&&key::enter(c)) {
		file->newline(currx, curry);
		setxy(0, curry+1);

		//update ruler to account for newlines
		ruler=std::log10(file->lines())+1;
	}
	//backspace is pressed at the start of a line
	else if (!isSuper&&key::backspace(c)&&currx==0&&curry!=0) {
		int tempx=file->linesize(curry-1);

		file->delline(curry);
		setxy(tempx, curry-1);

		ruler=std::log10(file->lines())+1;
	}
	else {
		if (isSuper) { //only changes to superx are needed in super mode
			//return if an invalid key was pressed
			if (key::down(c)||key::up(c)) return;

			superLine->insert(c, superx);
			if (key::backspace(c)&&superx!=0) superx--;
			else if (!key::backspace(c)) superx++;
		}
		else { //key was pressed when not in super mode
			int tmpx=currx;

			setxy(0, curry);
			write(file->insert(c, tmpx, curry));

			if (key::backspace(c)) setxy(tmpx-1, curry);
			else setxy(tmpx+1, curry);
		}
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