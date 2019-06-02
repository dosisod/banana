#include <vector>
#include <string>
#include <cmath>

#include "screen.hpp"

Screen::Screen() {
	setlocale(LC_ALL, ""); //allow for unicode
	window=initscr(); //init and clear screen
	start_color();
	noecho(); //dont print characters to screen

	keypad(window, true); //allows arrow keys to be detected
	ESCDELAY=0;

	update();
	refresh();

	//setup colors
	init_pair(1, COLOR_BLACK, COLOR_YELLOW);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_BLACK, COLOR_WHITE);
}

void Screen::super() {
	isSuper=true;

	render(0,1);

	wmove(window, 0, 0);
	attron(COLOR_PAIR(3));
	write(std::string(termx, ' '));
	wmove(window, 0, 0);

	int c=getch();
	while (c!=27&&c!=KEY_ENTER&&c!='\n') {
		write(std::string(1, c));
		c=getch();
	}
}

void Screen::update() {
	getmaxyx(window, termy, termx);
}

Screen::~Screen() {
	endwin();
}

void Screen::write(std::string s) {
	addstr(s.c_str());
}

void Screen::pause() {
	getch();
}

void Screen::parseKey(int c) {
	if (c==27) {
		super();
	}
	else if (c==KEY_UP) {
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
	else if (c=='\n'||c==KEY_ENTER) {
		file->newline(currx, curry);
		setxy(0, curry+1);

		//update ruler to account for newlines
		ruler=std::log10(file->lines())+1;
	}
	else if (c==KEY_BACKSPACE&&currx==0&&curry!=0) {
		file->delline(curry);
		setxy(file->linesize(curry-1), curry-1);

		ruler=std::log10(file->lines())+1;
	}
	else {
		int tmpx=currx;

		setxy(0, curry);
		write(file->insert(c, tmpx, curry));

		if (c==KEY_BACKSPACE) setxy(tmpx-1, curry);
		else setxy(tmpx+1, curry);
	}
}

void Screen::parseKeys(std::vector<int> c) {
	for (auto i:c) {
		parseKey(i);
	}
}

void Screen::home() {
	setxy(0, 0);
}

void Screen::setxy(int x, int y) {
	//must be checked first or file->line(-1) could happen
	if (y<0||y>=file->lines()) return;

	//prevents cursor getting stuck when going to a shorter line
	if (x>((int)file->line(y).length())) {
		x=file->line(y).length();
	}

	//make sure cursor stays within bounds
	if (
		x<0||
		x>=(termx-ruler-3)||
		y>termy
	) return;

	currx=x; //update current position
	curry=y; //
	wmove(window, y, x+ruler+1);
}

void Screen::delta(int dx, int dy) {
	setxy(dx+currx, dy+curry);
}

void Screen::render() {
	render(0, 0);
}

void Screen::render(int fy, int ty) {
	int tmpx=currx;
	int tmpy=curry;

	wmove(window, ty, 0); //force go to home

	int lines=file->lines()-fy; //dont want to call this every time

	for (int i=0;i<termy;i++) { //must go through all lines to fully clear screen
		if (i<lines) {
			attron(COLOR_PAIR(1)); //switch to black on yellow

			int space=ruler-(int)(std::log10(i+1)+1); //calculate left spacing
			if (space>=0) write(std::string(space, ' '));

			write(std::to_string(i+1)+" "); //print line number

			attron(COLOR_PAIR(2)); //switch to white on black

			//display line buffer
			if (wordwrap) write(file->line(i+fy)+"\n");
			else write(file->line(i+fy).substr(0, termx-ruler-2)+"\n");
		}
		else {
			attron(COLOR_PAIR(2));
			write("\n"); //put something to make sure line clears
		}
	}
	setxy(tmpx, tmpy); //move back to where the cursor was before
}

void Screen::useBuffer(File* f) {
	file=f;
	ruler=std::log10(file->lines())+1;
}