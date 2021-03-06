#pragma once

#include <memory>

#include "command.hpp"

class Commander {
public:
	Commander(std::vector<std::shared_ptr<Command>> commands);

	const typedef std::pair<std::string, std::string> Params;

	//returns parsed parameters
	Params parse(std::string str) const;

	//parses and call function accordingly
	void run(std::string str) const;

private:
	const std::vector<std::shared_ptr<Command>> commands;
};