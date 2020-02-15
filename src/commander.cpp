#include "commander.hpp"

Commander::Commander(std::vector<std::shared_ptr<Command>> commands) :
	commands(commands)
	{}

Commander::params Commander::parse(std::string str) {
	int pos=(int)str.find(' ');

	//default values if there is no space
	std::string p1=str;
	std::string p2="";

	if (pos > -1) {
		//update if there is a space
		p1=str.substr(0, pos);
		p2=str.substr(pos + 1);
	}

	return params { p1, p2 };
}

void Commander::run(std::string str) {
	params p=parse(str);

	for (auto command : commands) {
		if (command->check(p.first)) {
			command->run(p.second);

			break;
		}
	}
}