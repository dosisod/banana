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

	if (c==KEY_UP) {
		delta(0, -1);
	}
	else if (c==KEY_DOWN) {
		delta(0, 1);
	}
	else if (c==KEY_LEFT) {
		if (currx==0&&curry>0) setxy(file->line(curry-1).length(), curry-1);
		else delta(-1, 0);
	}
	else if (c==KEY_RIGHT) {
		if (currx==(int)file->line(curry).length()&&curry<file->lines()) setxy(0, curry+1);
		else delta(1, 0);
	}
	else if (c==KEY_END) {
		setxy(file->line(curry).length(), curry);
	}
	else if (c==KEY_HOME) {
		setxy(0, curry);
	}
	else if (c!=KEY_BACKSPACE) {
		int tmpx=currx;

		setxy(0, curry);
		write(file->insert(c, tmpx, curry));
		setxy(tmpx+1, curry);
	}
}

void Screen::home() {
	setxy(0, 0);
}

void Screen::setxy(int x, int y) {
	//must be checked first or file->line(-1) could happen
	if (y<0) return;

	//prevents cursor getting stuck when going to a shorter line
	if (x>((int)file->line(y).length())) {
		x=file->line(y).length();
	}

	//make sure cursor stays within bounds
	if (
		x<0||
		x>=(termx-ruler-3)||
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