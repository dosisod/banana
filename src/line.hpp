#pragma once

#include <string>

class Line {
public:
	Line(std::string str, int tab);

	//gets tab-parsed string
	std::string get() const;

	std::string insert(int character, int x);
	std::string insert(std::string s, int x);

	std::string getRaw() const;

	std::string substr(int start) const;
	std::string substr(int start, int ende) const;

	int size() const;

	//find where the cursor really is in the string
	int decode(int x) const;

private:
	std::string str;

	//width of tab in spaces
	const int tabsize=4;
};