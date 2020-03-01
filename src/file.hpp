#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include "line.hpp"

class File {
public:
	File(std::string filename, int tabsize);

	//number of lines in file buffer
	int lines() const;

	//get lineNum from buffer
	std::string line(int lineNum) const;

	//get rawline "lineNum" from buffer
	std::string rawLine(int lineNum) const;

	//get length of line "lineNum"
	int linesize(int lineNum) const;

	//insert char c at line y, over x places, return modified line
	std::string insert(int character, int x, int y);
	std::string insert(std::string str, int x, int y);

	//convert cursor "x" on line "y" into string length
	int decode(int x, int y);

	//insert newline at given xy
	void newline(int x, int y);

	//delete line if backspace is hit at start of line
	void delline(int y);

	//gets the indent at the start of the line n
	std::string getIndent(int lineNum) const;

	void save();
	void saveas(std::string fn);

	std::string getfn() const;

private:
	std::string filename;

	//stream is here as it can be used when reading and writing
	std::fstream stream;

	//contains the lines of the file
	std::vector<std::shared_ptr<Line>> buffer;

	//add extra eol (newline) after file is written
	const bool eol=false;

	//overriden when initiated
	int tabsize=4;
};