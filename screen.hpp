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

	void super(); //go into super mode (command mode)

	void pause();

	void parseKey(int c); //parses and interprets key
	void parseKeys(std::vector<int> c); //parses and interprets an array of keys

	void write(std::string s);

	void render(); //draws state of file to screen
	void render(int fy, int ty); //render screen starting with file line y at terminal line y

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

	File* file; //stores the file buffer
	int ruler; //defined from file

	bool wordwrap=false; //whether or not to wrap text

	bool isSuper=false; //whether or not super is active
};

#endif