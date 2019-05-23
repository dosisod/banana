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
	return buffer[n];
}