#include <ncurses.h>
#include <string>

class Screen {
public:
	Screen();
	~Screen();

	void pause();

	void write(std::string s);

private:
	WINDOW* window;

	int x=0; //x and y of terminal
	int y=0;
};