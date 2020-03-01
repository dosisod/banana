#include "commander.hpp"

Commander::Commander(std::vector<std::shared_ptr<Command>> commands) :
	commands(commands)
	{}

Commander::Params Commander::parse(std::string str) const {
	const int pos=(int)str.find(' ');

	if (pos > -1) {
		//space was found, split it
		return {
			str.substr(0, pos),
			str.substr(pos + 1)
		};
	}

	//there was no space
	return { str, "" };
}

void Commander::run(std::string str) const {
	const Params p=parse(str);

	for (const auto& command : commands) {
		if (command->check(p.first)) {
			command->run(p.second);

			break;
		}
	}
}