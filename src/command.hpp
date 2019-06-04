#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__

#include <functional>
#include <string>
#include <vector>

class Command {
public:
	//s is a space-seperated list of command names
	//eg, "save s" will mean that "save" and "s" are both valid command names
	//f is a lambda that parses the data after the first word
	Command(std::string c, std::function<void(std::string)> f);

	bool check(std::string s); //check is string is a valid command name
	void run(std::string s); //runs the internal function

private:
	std::vector<std::string> calls;

	std::function<void(std::string)> func;
};

#endif