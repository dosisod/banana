#include <cmath>

#include "screen.hpp"

//This file contains sections related to rendering the screen

void Screen::render() {
	render(filey, 0);
}

void Screen::render(int fy, int ty) {
	int tmpx=currx;
	int tmpy=curry;

	term->move(0, ty); //force go to home

	int lines=file->lines()-fy; //dont want to call this every time

	for (int i=0;i<term->gety()-ty;i++) { //must go through all lines to fully clear screen
		if (i<lines) {
			attron(COLOR_PAIR(1)); //switch to black on yellow

			int space=ruler-(int)(std::log10(i+fy+1)+1); //calculate left spacing
			if (space>=0) term->write(std::string(space, ' '));

			term->write(std::to_string(i+fy+1)+" "); //print line number

			attron(COLOR_PAIR(2)); //switch to white on black

			//display line buffer
			if (wordwrap) {
				term->write(file->line(i+fy)+"\n");
			}
			else {
				term->write(file->line(i+fy).substr(0, term->getx()-ruler-2)+"\n");
			}
		}
		else {
			attron(COLOR_PAIR(2));
			term->write("\n"); //put something to make sure line clears
		}
	}
	setxy(tmpx, tmpy); //move back to where the cursor was before
	term->move(currx+ruler+1, curry+ty); //move relative to the "ty" offset
}