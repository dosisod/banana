#include "commander.hpp"

Commander::Commander(std::vector<std::shared_ptr<Command>> c) {
	commands=c;
}

std::pair<std::string, std::string> Commander::parse(std::string str) {
	int pos=(int)str.find(' ');

	std::string p1=str; //default values if there is no space
	std::string p2="";

	if (pos>-1) { //update if there is a space
		p1=str.substr(0, pos);
		p2=str.substr(pos+1);
	}

	return std::pair<std::string, std::string> {p1, p2};
}

void Commander::run(std::string str) {
	std::pair<std::string, std::string> param=parse(str);

	for (auto i:commands) { //loop through all commands
		if (i->check(param.first)) { //if passed string is a call
			i->run(param.second); //run it
			return; //stop searching for more commands
		}
	}
}