#include <ncurses.h>
#include <string>

#include "file.hpp"

class Screen {
public:
	Screen();
	~Screen();

	void pause();

	void write(std::string s);

	void render(File* f);

	void home();
	void setxy(int x, int y);

private:
	WINDOW* window;

	int x, y; //x and y of terminal
};