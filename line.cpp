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
	std::string ret="";

	int counter=0;
	for (int i=0;i<(int)str.length();i++) {
		if (str[i]=='\t') {
			int tmp;
			if (tabsize-(counter%4)==0) tmp=tabsize-1;
			else tmp=tabsize-(counter%4);

			counter+=tmp;
			ret+=std::string(tmp, ' ');
		}
		else {
			ret+=str[i];
		}
		counter++;
	}
	return ret;
}

std::string Line::insert(char c, int x) {
	x=decode(x);
	//insert char at x pos
	str=str.substr(0, x)+c+str.substr(x);

	return str;
}

int Line::decode(int a) {
	a++;
	int counter=0; //number of characters needed to display (eg tabs)
	int i=0;

	for (;i<=(int)str.length();i++) {
		if (str[i]=='\t') {
			counter+=tabsize-1;
		}
		counter++;
		if (counter>=a) {
			return i;
		}
	}
	return i;
}