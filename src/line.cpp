#include <ncurses.h>
#include <string>

#include "line.hpp"
#include "keys.hpp"

Line::Line(std::string s, int tab) {
	str=s;
	tabsize=tab;
}

std::string Line::get() {
	std::string ret="";
	int counter=0;

	for (int i=0;i<(int)str.length();i++) {
		if (str[i]=='\t') {
			int tmp;
			if (counter%4==0) tmp=tabsize; //if tab is filled add a full new tab
			else tmp=tabsize-((counter)%4); //calculate space for remaining tab

			counter+=tmp-1;
			ret+=std::string(tmp, ' '); //add spacing to return
		}
		else ret+=str[i]; //single character, add to return

		counter++; //all chars take up at least one space
	}
	return ret;
}

std::string Line::getRaw() {
	return str;
}

std::string Line::substr(int s) {
	return getRaw().substr(decode(s));
}

std::string Line::substr(int s, int e) {
	return getRaw().substr(decode(s), decode(e));
}

int Line::size() {
	return get().length();
}

std::string Line::insert(int c, int x) {
	if (key::backspace(c)) {
		if (x!=0) str=str.substr(0, x-1)+str.substr(x);
	}
	//insert char at x pos
	else str=str.substr(0, x)+(char)c+str.substr(x);

	return get(); //return the parsed version
}

int Line::decode(int x) {
	if (str.length()==0) return 0;

	int counter=0;
	int i=0;
	for (;i<(int)str.length();i++) {
		if (counter>x) return i-1; //over calculated position, return last index
		if (counter==x) return i; //calculated exactly

		if (str[i]=='\t') {
			int tmp=tabsize-(counter%tabsize); //calculate tab size
			if (counter<x&&x<(counter+tmp)) { //if cursor is between a tab, return index of tab
				return i+1;
			}
			else if (tmp==0) counter+=tabsize; //if tab space is 0 add a whole new tab
			else counter+=tmp;
		}
		else {
			counter++; //normal character just add one
		}
	}
	return i;
}