#pragma once

#include <memory>

#include "command.hpp"

class Commander {
public:
	Commander(std::vector<std::shared_ptr<Command>> commands);

	const typedef std::pair<std::string, std::string> params;

	//returns parsed parameters
	params parse(std::string str);

	//parses and call function accordingly
	void run(std::string str);

private:
	std::vector<std::shared_ptr<Command>> commands;
};