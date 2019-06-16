#ifndef __SCREEN_HPP__
#define __SCREEN_HPP__

#include <ncurses.h>
#include <vector>
#include <string>
#include <memory>

#include "commander.hpp"
#include "terminal.hpp"
#include "file.hpp"

class Screen {
public:
	Screen(std::shared_ptr<Terminal> t); //create screen instance
	~Screen(); //close everything nicely

	void pause();

	void parseKey(int c); //parses and interprets key
	void parseKeys(std::vector<int> c); //parses and interprets an array of keys

	void render(); //draws state of file to screen
	void render(int fy, int ty); //render screen starting with file line y at terminal line y

	void home(); //goto home position
	void setxy(int x, int y);
	void delta(int dx, int dy); //move cursor relative to current pos

	void useBuffer(std::shared_ptr<File> f); //switch which buffer to use

	std::shared_ptr<File> file; //stores the file buffer

private:
	std::shared_ptr<Terminal> term; //stores common terminal object

	int currx=0;
	int curry=0; //current xy of cursor

	int ruler; //defined from file

	bool wordwrap=false; //whether or not to wrap text
};

#endif