#ifndef __TERMINAL_HPP__
#define __TERMINAL_HPP__

#include <ncurses.h>
#include <vector>
#include <string>

//terminal should be used as if it is static, and passed via pointers to functions that need it

class Terminal {
public:
	Terminal(); //creates the terminal instance

	void write(std::string s);

	void update();

	void move(int x, int y); //move to raw position x y

private:
	WINDOW* window;

	int x, y; //x and y dimension of terminal
};

#endif