#include <cmath>

#include "screen.hpp"

//This file contains sections related to rendering the screen

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

void Screen::write(std::string s) {
	addstr(s.c_str());
}

void Screen::update() {
	getmaxyx(window, termy, termx);
}