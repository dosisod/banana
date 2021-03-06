#pragma once

#include <functional>
#include <string>
#include <vector>

class Command {
public:
	//call is a space-seperated list of command names
	//func is a lambda to be ran when the command is activated
	Command(std::string call, std::function<void(std::string)> func);
	Command(std::string call, std::function<void()> func);

	//check if string is a valid command name
	bool check(std::string command) const;

	//runs func
	void run(std::string command) const;

private:
	std::vector<std::string> calls;

	const std::function<void(std::string)> func;
};