#ifndef __FILE_HPP__
#define __FILE_HPP__

#include <fstream>
#include <string>
#include <vector>

#include "line.hpp"

class File {
public:
	File(std::string fn);

	int lines(); //number of lines in file buffer
	std::string line(int n); //get line N from buffer
	int linesize(int n); //get length of line N

	//insert char c at line y, over x places, return modified line
	std::string insert(char c, int x, int y);

	void newline(int x, int y); //insert newline at given xy

private:
	std::string filename;

	std::fstream stream; //stream is here as it can be used when reading and writing
	std::vector<Line*> buffer; //contains the lines of the file

	int tabsize=4; //tabs are rendered as N spaces, and but will still be tabs after saving
};

#endif