#include <fstream>
#include <vector>
#include <string>

#include "file.hpp"
#include "line.hpp"

File::File(std::string fn) {
	filename=fn;
	stream.open(filename);

	if (stream.is_open()) {
		std::string line="";
		while (std::getline(stream, line)) {
			buffer.push_back(new Line(line));
		}
	}
	stream.close();
}

int File::lines() {
	return buffer.size();
}

std::string File::line(int n) {
	return buffer[n]->get();
}

int File::linesize(int n) {
	return (int)line(n).length();
}

std::string File::insert(char c, int x, int y) {
	//insert char at x pos then return it
	return buffer[y]->insert(c, x);
}

void File::newline(int x, int y) {
	//used to insert a new line buffer
	std::vector<Line*>::iterator it=buffer.begin();

	//add new line
	buffer.insert(it+y+1, new Line(buffer[y]->get().substr(x)));

	//set the line that was split to the new parsed line
	buffer[y]=new Line(buffer[y]->get().substr(0,x));
}