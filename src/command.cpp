#include <cstring>

#include "command.hpp"

Command::Command(std::string c, std::function<void(std::string)> f) {
	int last=0;
	std::string tmp="";

	for (int i=0;i<=(int)c.length();i++) {
		if (c[i]==' '||i==(int)c.length()) { //split if at a space or eol
			tmp=c.substr(last, i);
			if (tmp!="") calls.push_back(tmp);
			last=i;
		}
	}

	func=f;
}

bool Command::check(std::string s) {
	for (auto i:calls) {
		if (i==s) return true;
	}
	return false;
}

void Command::run(std::string s) {
	func(s);
}