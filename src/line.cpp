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

int Line::size() {
	return get().length();
}

std::string Line::insert(int c, int x) {
	x=decode(x);

	if (key::backspace(c)) {
		if (x!=0) str=str.substr(0, x-1)+str.substr(x);
	}
	//insert char at x pos
	else str=str.substr(0, x)+(char)c+str.substr(x);

	return get(); //return the parsed version
}

int Line::decode(int a) {
	int counter=0; //number of characters needed to display (eg tabs)

	int i=0;
	for (;i<(int)str.length();i++) {
		if (str[i]=='\t') { //calculate how much space the tab takes up
			int tmp;
			if (counter%4==0) tmp=tabsize;
			else tmp=tabsize-((counter)%4);

			counter+=tmp-1;
		}
		if (counter>=a) return i; //keep counting untill the correct character is found

		counter++;
	}
	return i;
}