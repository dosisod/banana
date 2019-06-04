#include "commander.hpp"

Commander::Commander(std::vector<Command*> c) {
	commands=c;
}

void Commander::parse(std::string s) {
	for (auto i:commands) { //loop through all commands
		if (i->check(s)) { //if passed string is a call
			i->run(s); //run it
			return; //stop searching for more commands
		}
	}
}