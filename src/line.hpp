#ifndef __LINE_HPP__
#define __LINE_HPP__

#include <string>

class Line {
public:
	//creates a new line object from string
	Line(std::string str);

	std::string insert(int c, int x);

	std::string get(); //gets tab-parsed string
	std::string getRaw(); //returns raw string

	int size(); //returns size of get()

private:
	std::string str; //string containing line data

	int decode(int x); //find where the cursor really is in the string

	int tabsize=4; //tabs are rendered as N spaces, and but will still be tabs after saving
};

#endif