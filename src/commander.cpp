#include "commander.hpp"

Commander::Commander(std::vector<std::shared_ptr<Command>> c) {
	commands=c;
}

Commander::params Commander::parse(std::string str) {
	int pos=(int)str.find(' ');

	std::string p1=str; //default values if there is no space
	std::string p2="";

	if (pos>-1) { //update if there is a space
		p1=str.substr(0, pos);
		p2=str.substr(pos+1);
	}

	return params {p1, p2};
}

void Commander::run(std::string str) {
	params p=parse(str);

	for (auto i:commands) { //loop through all commands
		if (i->check(p.first)) { //if passed string is a call
			i->run(p.second); //run it
			return; //stop searching for more commands
		}
	}
}