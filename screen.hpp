#ifndef __SCREEN_HPP__
#define __SCREEN_HPP__

#include <ncurses.h>
#include <vector>
#include <string>

#include "file.hpp"

class Screen {
public:
	Screen(); //create blank screen
	~Screen(); //close everything nicely

	void pause();

	void parseKey(int c); //parses and interprets key
	void parseKeys(std::vector<int> c); //parses and interprets an array of keys

	void write(std::string s);

	void render(); //draws state of file to screen

	void home(); //goto home position
	void setxy(int x, int y);
	void delta(int dx, int dy); //move cursor relative to current pos

	void useBuffer(File* f); //switch which buffer to use

private:
	WINDOW* window;

	int currx=0;
	int curry=0; //current xy of cursor

	int termx, termy; //x and y dimension of terminal
	void update(); //updates x and y

	File* file; //needed for proper spacing
	int ruler; //defined from file

	bool wordwrap=false; //whether or not to wrap text
};

#endif