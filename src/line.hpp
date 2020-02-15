#pragma once

#include <string>

class Line {
public:
	Line(std::string str, int tab);

	//gets tab-parsed string
	std::string get();

	std::string insert(int character, int x);
	std::string insert(std::string s, int x);

	std::string getRaw();

	std::string substr(int start);
	std::string substr(int start, int ende);

	int size();

	//find where the cursor really is in the string
	int decode(int x);

private:
	std::string str;

	//width of tab in spaces
	int tabsize=4;
};