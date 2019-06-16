#ifndef __SCREENMASTER_HPP__
#define __SCREENMASTER_HPP__

#include <memory>
#include <vector>

#include "terminal.hpp"
#include "screen.hpp"

class ScreenMaster {
public:
	ScreenMaster(std::shared_ptr<Terminal> t);
	~ScreenMaster();

	void addBuffer(std::string s); //adds a new screen buffer using file buffer initializer

	void parseKey(int c);

	std::shared_ptr<Screen> operator->(); //all -> functions done to master are passed to current screen
	std::shared_ptr<Screen> screen(); //get current screen

private:
	std::shared_ptr<Terminal> term;

	std::vector<std::shared_ptr<Screen>> screens;
	int currentscr=-1; //holds id of current screen

	void super(); //handles super line
	void superParse(int c); //handles input to superline
	std::shared_ptr<Line> superLine; //stores line for super mode

	int superx=0; //x position of cursor when in super mode
	bool isSuper=false; //whether or not super is active

	std::shared_ptr<Commander> commands; //pointer for storing the commander
};

#endif