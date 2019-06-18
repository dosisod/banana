#ifndef __COMMANDER_HPP__
#define __COMMANDER_HPP__

#include <memory>

#include "command.hpp"

class Commander { //holds all of the commands to be used
public:
	Commander(std::vector<std::shared_ptr<Command>> c);

	std::pair<std::string, std::string> parse(std::string str); //returns parsed parameters
	void run(std::string str); //parses and call function accordingly

private:
	std::vector<std::shared_ptr<Command>> commands;
};

#endif