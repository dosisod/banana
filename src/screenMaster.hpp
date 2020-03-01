#pragma once

#include <memory>
#include <vector>

#include "terminal.hpp"
#include "screen.hpp"

class ScreenMaster {
public:
	ScreenMaster(std::shared_ptr<Terminal> terminal);
	~ScreenMaster();

	void addBuffer(std::string s);

	void parseKey(int c);

	void pause()const ;

	//forward -> calls to current screen
	std::shared_ptr<Screen> operator->() const;

	std::shared_ptr<Screen> screen() const;

	int screenid() const;

	int parsenum(std::string str, int fail);

private:
	const std::shared_ptr<Terminal> terminal;

	std::vector<std::shared_ptr<Screen>> screens;

	int currentscr=-1;

	//runs super mode code
	void super();

	//handles input to superline
	void superParse(int c);

	//stores line for super mode
	std::shared_ptr<Line> superLine;

	//x position of cursor when in super mode
	int superx=0;

	const int tabsize=4;

	std::shared_ptr<Commander> commands;

	//stores keys used by the "macronew" command
	std::vector<int> mn_keys;
};