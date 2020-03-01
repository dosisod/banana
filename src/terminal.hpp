#pragma once

#include <ncurses.h>
#include <vector>
#include <string>

//terminal should be used as if it is static, and passed via pointers to functions that need it

class Terminal {
public:
	Terminal();

	void write(std::string str) const;

	void clear(int y) const;

	//clear line "y" and write "str"
	void zero(int y, std::string str) const;

	//updates terminal x and y
	void update();

	void move(int x, int y) const;

	//max x and y of terminal
	int getx() const;
	int gety() const;

private:
	WINDOW* window;

	//terminal x and y
	int x;
	int y;
};