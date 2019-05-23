#include <ncurses.h>
#include <string>

#include "file.hpp"

class Screen {
public:
	Screen(); //create blank screen
	~Screen(); //close everything nicely

	void pause();

	void write(std::string s);

	void render();

	void home(); //goto home position
	void setxy(int x, int y);

	void useBuffer(File* f); //switch which buffer to use

private:
	WINDOW* window;

	int x, y; //x and y of terminal

	File* file; //needed for proper spacing
	int ruler; //defined from file
};