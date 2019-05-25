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

	int currx=0;
	int curry=0; //current xy of cursor

	int termx, termy; //x and y dimension of terminal
	void update(); //updates x and y

	File* file; //needed for proper spacing
	int ruler; //defined from file
};