#include <cstring>

#include "command.hpp"

Command::Command(std::string call, std::function<void(std::string)> func) :
	func(func)
{
	int last=0;
	std::string tmp="";

	for (int i=1 ; i <= (int)call.length() ; i++) {
		if (call[i]==' ' || i==(int)call.length()) {
			//split if at a space or eol
			tmp=call.substr(last, i - last);

			if (tmp!="") {
				calls.push_back(tmp);
			}
			last=i + 1;
		}
	}
}

Command::Command(std::string call, std::function<void()> func) :
	Command(call, [=](std::string s){
		func();
	}) {}

bool Command::check(std::string command) const {
	for (auto call : calls) {
		if (call==command) return true;
	}
	return false;
}

void Command::run(std::string command) const {
	func(command);
}