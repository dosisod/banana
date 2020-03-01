#include <ncurses.h>
#include <string>

#include "line.hpp"
#include "keys.hpp"

Line::Line(std::string str, int tabsize) :
	tabsize(tabsize),
	str(str)
	{}

std::string Line::get() const {
	std::string ret="";
	int counter=0;

	for (int i=0; i < (int)str.length() ; i++) {
		if (str[i]=='\t') {
			int tmp;
			if (counter % 4 == 0) {
				//if tab is filled add a full new tab
				tmp=tabsize;
			}
			else {
				//calculate space for remaining tab
				tmp=tabsize - (counter % 4);
			}

			counter+=tmp - 1;

			ret+=std::string(tmp, ' ');
		}
		else {
			//single character, add to return
			ret+=str[i];
		}

		//all chars take up at least one space
		counter++;
	}

	return ret;
}

std::string Line::getRaw() const {
	return str;
}

std::string Line::substr(int start) const {
	return getRaw().substr(
		decode(start)
	);
}

std::string Line::substr(int start, int end) const {
	return getRaw().substr(
		decode(start),
		decode(end)
	);
}

int Line::size() const {
	return get().length();
}

std::string Line::insert(int character, int x) {
	if (key::backspace(character)) {
		if (x!=0) {
			str=str.substr(0, x - 1) + str.substr(x);
		}
	}

	else {
		//insert char at x pos

		str=str.substr(0, x) +
			(char)character +
			str.substr(x);
	}

	return get();
}

std::string Line::insert(std::string s, int x) {
	for (const auto character : str) {
		if (
			!key::valid(character) ||
			key::backspace(character) ||
			key::enter(character)
		) {
			return "";
		}
	}

	str=str.substr(0, x) + s + str.substr(x);

	return get();
}

int Line::decode(int x) const {
	if (str.length()==0) {
		return 0;
	}

	int counter=0;
	int i=0;

	for (;i<(int)str.length();i++) {
		if (counter > x) {
			//over calculated position, return last index
			return i - 1;
		}

		else if (counter == x) {
			//calculated exactly
			return i;
		}

		if (str[i]=='\t') {
			//calculate tab size
			const int tmp=tabsize-(counter%tabsize);

			if (counter < x && x <(counter + tmp)) {
				//cursor is between a tab, return index of tab
				return i + 1;
			}
			else if (tmp==0) {
				//tab space is 0 add a whole new tab
				counter+=tabsize;
			}
			else {
				counter+=tmp;
			}
		}
		else {
			//normal character, just add one
			counter++;
		}
	}
	return i;
}