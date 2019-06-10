#include <vector>
#include <string>
#include <cmath>

#include "commander.hpp"
#include "command.hpp"
#include "screen.hpp"
#include "keys.hpp"

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

	commands=new Commander(std::vector<Command*>({
		new Command("save s", [=](std::string s){ file->save(); } ),
		new Command("saveas sa", [=](std::string s){ file->saveas(s); } ),
		new Command("quit exit q", [=](std::string s) {
			this->~Screen(); //calls deconstructor then quits
			exit(0);
		})
	}));
}

void Screen::super() {
	isSuper=true;

	//clear from last time super was active
	superx=0;
	superLine=new Line("");

	render(0,1); //move all lines down one

	wmove(window, 0, 0);
	attron(COLOR_PAIR(3));
	write(std::string(termx, ' ')); //fill line with white space
	wmove(window, 0, 0);

	int c=getch();
	while (!key::escape(c)&&!key::enter(c)) {
		wmove(window, 0, 0); //goto start of line
		write(std::string(termx, ' ')); //fill line with white space
		wmove(window, 0, 0); //go back to start of line

		parseKey(c); //parse key press
		write(superLine->get()); //write line
		wmove(window, 0, superx); //move cursor back to correct position

		c=getch();
	}
	if (key::enter(c)) commands->parse(superLine->getRaw());

	isSuper=false;
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
		//setxy(file->linesize(curry-1), curry-1);
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

void Screen::home() {
	setxy(0, 0);
}

void Screen::setxy(int x, int y) {
	//must be checked first or file->line(-1) could happen
	if (y<0||y>=file->lines()) return;

	//prevents cursor getting stuck when going to a shorter line
	if (x>(file->linesize(y))) {
		x=file->linesize(y);
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