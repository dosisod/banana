#ifndef __SCREENMASTER_HPP__
#define __SCREENMASTER_HPP__

#include <memory>
#include <vector>

#include "terminal.hpp"
#include "screen.hpp"

class ScreenMaster {
public:
	ScreenMaster();

	void addBuffer(std::string s); //adds a new screen buffer using file buffer initializer

private:
	std::shared_ptr<Terminal> term;

	std::vector<std::shared_ptr<Screen>> screens;
};

#endif