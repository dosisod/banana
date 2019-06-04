#include "commander.hpp"

Commander::Commander(std::vector<Command*> c) {
	commands=c;
}

void Commander::parse(std::string s) {
	int pos=(int)s.find(' ');

	std::string p1=s; //default values if there is no space
	std::string p2="";

	if (pos>-1) { //update if there is a space
		p1=s.substr(0, pos);
		p2=s.substr(pos+1);
	}

	for (auto i:commands) { //loop through all commands
		if (i->check(p1)) { //if passed string is a call
			i->run(p2); //run it
			return; //stop searching for more commands
		}
	}
}