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
	void clear(int y); //clear line "y"
	void zero(int y, std::string s); //clear line "y" and write "s"

	void update(); //updates x and y of terminal

	void move(int x, int y); //move to raw position x y

	int getx(); //return x and y of screen
	int gety(); //

private:
	WINDOW* window;

	int x; //x and y dimension of terminal
	int y; //
};

#endif