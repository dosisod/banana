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
	std::string getIndent(); //gets the indent at the start of the line

	int size(); //returns size of get()

private:
	std::string str; //string containing line data

	int decode(int x); //find where the cursor really is in the string

	int tabsize=4; //tabs are rendered as N spaces, and but will still be tabs after saving
};

#endif