#pragma once

#include <ncurses.h>
#include <vector>
#include <string>

//terminal should be used as if it is static, and passed via pointers to functions that need it

class Terminal {
public:
	Terminal();

	void write(std::string str);

	void clear(int y);

	//clear line "y" and write "str"
	void zero(int y, std::string str);

	//updates terminal x and y
	void update();

	void move(int x, int y);

	//max x and y of terminal
	int getx();
	int gety();

private:
	WINDOW* window;

	//terminal x and y
	int x;
	int y;
};