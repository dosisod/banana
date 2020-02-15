#include <cmath>

#include "screen.hpp"

void Screen::render() {
	render(filey, 0);
}

void Screen::render(int fy, int ty) {
	int tmpx=currx;
	int tmpy=curry;

	terminal->move(0, ty);

	//dont want to call this every time
	int lines=file->lines() - fy;

	//must go through all lines to fully clear screen
	for (int i=0 ; i < terminal->gety() - ty ; i++) {
		if (i < lines) {
			attron(COLOR_PAIR(1));

			//calculate left spacing
			int space=ruler - (int)(std::log10(i + fy + 1) + 1);
			if (space >= 0) {
				terminal->write(std::string(space, ' '));
			}

			//print line number
			terminal->write(std::to_string(i + fy + 1) + " ");

			attron(COLOR_PAIR(2));

			if (wordwrap) {
				terminal->write(file->line(i + fy) + "\n");
			}
			else {
				terminal->write(
					file->line(i + fy).substr(
						0,
						terminal->getx() - ruler - 2
					) + "\n"
				);
			}
		}
		else {
			attron(COLOR_PAIR(2));
			terminal->write("\n");
		}
	}

	//move back to where the cursor was before
	setxy(tmpx, tmpy);

	//move cursor to start of closest character to the right
	terminal->move(
		encode(
			file->rawLine(realy()).substr(
				0,
				decode(currx, realy())
			)
		) + ruler + 1,
		curry + ty
	);
}