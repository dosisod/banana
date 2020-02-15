#include <cmath>

#include "screen.hpp"
#include "keys.hpp"

void Screen::pause() {
	getch();
}

void Screen::parseKey(int c) {
	if (key::del(c)) {
		int tmpy=curry;
		int tmpx=currx;

		parseKey(KEY_RIGHT);

		if (tmpy==curry && file->linesize(realy())==0) {
			return;
		}

		if (
			currx < file->linesize(realy()) ||
			tmpx!=currx ||
			tmpy!=curry
		) parseKey(KEY_BACKSPACE);

		return;
	}
	else if (key::up(c)) {
		delta(0, -1);
	}
	else if (key::pageup(c)) {
		delta(0, -page);
	}
	else if (key::down(c)) {
		delta(0, 1);
	}
	else if (key::pagedown(c)) {
		delta(0, page);
	}
	else if (key::left(c)) {
		if (currx==0 && (curry + filey) > 0) {
			//left was pressed while at the start of a line
			setxy(
				file->linesize(
					curry + filey - 1
				),
				curry - 1
			);
		}
		else {
			//left was pressed somewhere else
			delta(-1, 0);
		}
	}
	else if (key::right(c)) {
		//right was pressed at the end of a line
		if (currx==file->linesize(realy()) && realy() + 1 < file->lines()) {
			setxy(0, curry+1);
		}
		else {
			//right was pressed somewhere else
			delta(1, 0);
		}
	}
	else if (key::end(c)) {
		setxy(
			file->linesize(
				curry + filey
			),
			curry
		);
	}
	else if (key::home(c)) {
		setxy(0, curry);
	}
	else if (key::enter(c)) {
		//split line at cursor position
		file->newline(
			currx,
			curry + filey
		);

		//move cursor to new pposition
		setxy(
			encode(
				file->line(
					curry + filey
				)
			),
			curry + 1
		);

		//update ruler to account for newlines
		ruler=std::log10(file->lines()) + 1;

		std::string lastline=file->rawLine(curry + filey - 1);

		//auto indent brackets
		if (key::bracketRight(charCurrent()) && key::bracketLeft(lastline[lastline.length() - 1])) {
			parseKeys(std::vector<int>{
				KEY_UP,
				KEY_END,
				KEY_ENTER,
				'\t'
			});
		}
	}

	//backspace is pressed at the start of a line
	else if (key::backspace(c) && currx==0 && (curry + filey)!=0) {
		int tempx=file->linesize(curry + filey - 1);

		file->delline(curry + filey);
		setxy(tempx, curry - 1);

		ruler=std::log10(file->lines()) + 1;
	}
	else if (key::valid(c)) {
		//only move cursor when a closing bracket is pressed next to a closed bracket
		if (key::bracketRight(c) && charAt(currx, curry + filey)==c) {
			setxy(currx + 1, curry);
		}
		else if (key::bracketRight(charOver(1, 0)) && key::backspace(c) && key::bracketLeft(charCurrent())) {
			parseKeys(std::vector<int>{
				KEY_RIGHT,
				KEY_BACKSPACE,
				KEY_BACKSPACE
			});
		}

		//normal character was pressed
		else {
			int tmpx=currx;

			setxy(0, curry);

			terminal->write(file->insert(
				c,
				decode(tmpx, realy()),
				realy()
			));

			if (key::backspace(c)) {
				//move cursor back
				setxy(tmpx - 1, curry);
			}
			else if (key::bracketLeft(c)) {
				setxy(0, curry);

				//insert closing bracket
				terminal->write(file->insert(
					key::bracketize(c),
					decode(tmpx + 1, realy()),
					realy()
				));

				//then move back one
				setxy(tmpx + 1, curry);
			}
			else if (c=='\t') {
				setxy(
					tmpx + tabsize + (tmpx % tabsize),
					curry
				);
			}
			else {
				setxy(tmpx + 1, curry);
			}
		}
	}
}

void Screen::parseKeys(std::vector<int> keys) {
	for (auto i : keys) {
		parseKey(i);
	}
}

void Screen::useBuffer(std::shared_ptr<File> f) {
	file=f;
	ruler=std::log10(file->lines()) + 1;
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

	for (int i=0 ; i < (int)str.length() ; i++) {
		if (str[i]=='\t') {
			counter+=tabsize;
		}
		else {
			counter++;
		}
	}
	return counter;
}