#include <fstream>
#include <vector>
#include <string>

#include "file.hpp"

File::File(std::string fn) {
	filename=fn;
	stream.open(filename);

	if (stream.is_open()) {
		std::string line="";
		while (std::getline(stream, line)) {
			buffer.push_back(line);
		}
		stream.close();
	}
	stream.close();
}

int File::lines() {
	return buffer.size();
}

std::string File::line(int n) {
	std::string str=buffer[n];

	int tabs=0;
	for (int i=0;i<(int)str.length();i++) {
		if (str[i]=='\t') tabs++;
	}

	//replace tabs with spaces and append original line
	return std::string(tabs*tabsize, ' ')+buffer[n].substr(tabs);
}

int File::linesize(int n) {
	return (int)line(n).length();
}

std::string File::insert(char c, int x, int y) {
	//insert char at x pos
	//buffer[y]=buffer[y].substr(x, linesize(y))+c+buffer[y].substr(x);
	buffer[y]=buffer[y].substr(0, x)+c+buffer[y].substr(x);

	return buffer[y];
}