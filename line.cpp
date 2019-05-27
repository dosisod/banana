#include <string>

#include "line.hpp"

Line::Line(std::string s) {
	str=s;
	tabs=0;

	for (int i=0;i<(int)s.length();i++) {
		if (s[i]=='\t') tabs++;
	}
}

std::string Line::get() {
	//replace tabs with spaces and append original line
	return std::string(tabs*tabsize, ' ')+str.substr(tabs);
}

std::string Line::insert(char c, int x) {
	//insert char at x pos
	str=str.substr(0, x)+c+str.substr(x);

	return str;
}