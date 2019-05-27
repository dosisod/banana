#include <string>

class Line {
public:
	//creates a new line object from string
	Line(std::string str);

	std::string insert(char c, int x);

	std::string get();

private:
	std::string str; //string containing line data

	int tabs; //number of tabs before data
	int tabsize=4; //size of each tab
};