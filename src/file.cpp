#include <fstream>
#include <vector>
#include <string>

#include "file.hpp"
#include "line.hpp"

File::File(std::string filename, int tabsize) :
	filename(filename),
	tabsize(tabsize)
{
	stream.open(filename);

	if (stream.is_open()) {
		std::string line="";
		while (std::getline(stream, line)) {
			buffer.push_back(std::make_shared<Line>(line, tabsize));
		}
	}
	else {
		//append a single blank file
		buffer.push_back(std::make_shared<Line>("", tabsize));
	}
	stream.close();
}

int File::lines() const {
	return buffer.size();
}

std::string File::rawLine(int lineNum) const {
	return buffer[lineNum]->getRaw();
}

std::string File::line(int lineNum) const {
	return buffer[lineNum]->get();
}

int File::linesize(int lineNum) const {
	return buffer[lineNum]->size();
}

std::string File::insert(int character, int x, int y) {
	//insert char at x pos then return it
	return buffer[y]->insert(character, x);
}

std::string File::insert(std::string str, int x, int y) {
	//insert string s at x pos then return it
	return buffer[y]->insert(str, x);
}

int File::decode(int x, int y) {
	return buffer[y]->decode(x);
}

void File::newline(int x, int y) {
	auto iter=buffer.begin();

	std::string indent=getIndent(y);

	if (x < (int)indent.length()) {
		indent=indent.substr(0, x);
	}

	//add new line
	buffer.insert(
		iter + y + 1,
		std::make_shared<Line>(
			indent + buffer[y]->substr(x),
			tabsize
		)
	);

	//updates old line
	buffer[y]=std::make_shared<Line>(
		buffer[y]->substr(0, x),
		tabsize
	);
}

void File::delline(int y) {
	buffer[y-1]=std::make_shared<Line>(
		buffer[y-1]->getRaw() + buffer[y]->getRaw(),
		tabsize
	);

	//remove line that cursor was
	buffer.erase(buffer.begin() + y);
}

std::string File::getIndent(int lineNum) const {
	std::string tmp=rawLine(lineNum);
	int i=0;

	for (; i < (int)tmp.length() ;) {
		if (tmp[i]==' ' || tmp[i]=='\t') {
			i++;
		}
		else break;
	}
	return tmp.substr(0, i);
}

void File::save() {
	saveas(filename);
}

void File::saveas(std::string fn) {
	filename=fn;

	stream.open(filename, std::ios::out);

	for (int i=0 ; i < (int)buffer.size() ; i++) {
		stream << buffer[i]->getRaw();

		//add newlines to all lines except for last line
		if (i < (int)buffer.size() - 1) {
			stream << "\n";
		}
	}

	if (eol && buffer[buffer.size() - 1]->getRaw() != "") {
		stream << "\n";
	}

	stream.close();
}

std::string File::getfn() const {
	return filename;
}