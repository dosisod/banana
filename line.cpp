#include <string>

#include "line.hpp"

Line::Line(std::string s) {
	str=s;
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

std::string Line::insert(char c, int x) {
	x=decode(x);

	//insert char at x pos
	str=str.substr(0, x)+c+str.substr(x);

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