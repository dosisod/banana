#ifndef __TERMINAL_HPP__
#define __TERMINAL_HPP__

#include <ncurses.h>
#include <vector>
#include <string>

//terminal should be used as if it is static, and passed via pointers to functions that need it

class Terminal {
public:
	Terminal(); //creates the terminal instance

	void write(std::string s); //writes a string to the screen

	void update(); //updates x and y of terminal

	void move(int x, int y); //move to raw position x y

	int getx() { return x; } //return x and y of screen
	int gety() { return y; } //

private:
	WINDOW* window;

	int x, y; //x and y dimension of terminal
};

#endif