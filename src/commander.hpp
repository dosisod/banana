#ifndef __COMMANDER_HPP__
#define __COMMANDER_HPP__

#include "command.hpp"

class Commander { //holds all of the commands to be used
public:
	Commander(std::vector<Command*> c);

	void parse(std::string str); //parse and call function accordingly

private:
	std::vector<Command*> commands;
};

#endif