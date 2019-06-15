#ifndef __SCREENMASTER_HPP__
#define __SCREENMASTER_HPP__

#include <memory>
#include <vector>

#include "terminal.hpp"
#include "screen.hpp"

class ScreenMaster {
public:
	ScreenMaster(std::shared_ptr<Terminal> t);

	void addBuffer(std::string s); //adds a new screen buffer using file buffer initializer

	//all -> functions done to master are passed to current screen
	std::shared_ptr<Screen> operator->() {
		return screens[currentscr];
	}

private:
	std::shared_ptr<Terminal> term;

	std::vector<std::shared_ptr<Screen>> screens;
	int currentscr=0; //holds id of current screen
};

#endif