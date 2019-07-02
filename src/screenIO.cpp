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

		if (currx>=file->linesize(curry+filey)&&(curry+filey+2)>file->lines()) {
			return;
		}
		else if (currx>file->linesize(curry+filey)) {
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
		if (currx==0&&(curry+filey)>0) setxy(file->linesize(curry+filey-1), curry-1);

		//left was pressed somewhere else
		else delta(-1, 0);
	}
	else if (key::right(c)) {
		//right was pressed at the end of a line
		if (currx==(int)file->linesize(curry+filey)&&(curry+filey)<file->lines()) setxy(0, curry+1);

		//right was pressed somewhere else
		else delta(1, 0);
	}
	else if (key::end(c)) {
		setxy(file->linesize(curry+filey), curry);
	}
	else if (key::home(c)) {
		setxy(0, curry);
	}
	else if (key::enter(c)) {
		file->newline(currx, curry+filey); //split line at cursor position
		setxy(encode(file->line(curry+filey)), curry+1); //move cursor to new pposition

		//update ruler to account for newlines
		ruler=std::log10(file->lines())+1;

		//if cursor is between 2 matching brackets when enter is pressed, auto indent
		std::string lastline=file->rawLine(curry+filey-1);
		if (key::bracketRight(charCurrent())&&key::bracketLeft(lastline[lastline.length()-1])) {
			parseKeys(std::vector<int>{
				KEY_UP,
				KEY_END,
				KEY_ENTER,
				'\t'
			});
		}
	}
	//backspace is pressed at the start of a line
	else if (key::backspace(c)&&currx==0&&(curry+filey)!=0) {
		int tempx=file->linesize(curry+filey-1);

		file->delline(curry+filey);
		setxy(tempx, curry-1);

		ruler=std::log10(file->lines())+1;
	}
	else if (key::valid(c)) {
		//only move cursor when a closing bracket is pressed next to a closed bracket
		if (key::bracketRight(c)&&charAt(currx, curry+filey)==c) {
			setxy(currx+1, curry);
		}
		else { //normal character was pressed
			int tmpx=currx;

			setxy(0, curry);
			term->write(file->insert(c, decode(tmpx, curry+filey), curry+filey));

			if (key::backspace(c)) { //move cursor back
				setxy(tmpx-1, curry);
			}
			else if (key::bracketLeft(c)) {
				setxy(0, curry);

				//insert closing bracket
				term->write(file->insert(key::bracketize(c), decode(tmpx+1, curry+filey), curry+filey));

				//then move back one
				setxy(tmpx+1, curry);
			}
			else if (c=='\t') {
				setxy(
					tmpx+tabsize+(tmpx%tabsize),
					curry
				);
			}
			else {
				setxy(tmpx+1, curry);
			}
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

void Screen::useBuffer(std::string fn) {
	useBuffer(std::make_shared<File>(fn, tabsize));
}

int Screen::decode() {
	return decode(currx, curry);
}

int Screen::decode(int x, int y) {
	return file->decode(x, y);
}

int Screen::encode(std::string str) {
	int counter=0;

	for (int i=0;i<(int)str.length();i++) {
		if (str[i]=='\t') counter+=tabsize;
		else counter++;
	}
	return counter;
}