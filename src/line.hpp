#ifndef __LINE_HPP__
#define __LINE_HPP__

#include <string>

class Line {
public:
	//creates a new line object from string, and tabsize
	Line(std::string str, int tab);

	std::string insert(int c, int x);

	std::string get(); //gets tab-parsed string
	std::string getRaw(); //returns raw string
	std::string substr(int s); //substr using getRaw and decode
	std::string substr(int s, int e); //substr using getRaw and decode

	int size(); //returns size of get()

	int decode(int x); //find where the cursor really is in the string

private:
	std::string str; //string containing line data

	int tabsize=4; //tabs are rendered as N spaces, and but will still be tabs after saving
};

#endif