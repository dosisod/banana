#include <fstream>
#include <vector>
#include <string>

#include "file.hpp"
#include "line.hpp"

File::File(std::string fn, int tab) {
	tabsize=tab;

	filename=fn;
	stream.open(filename);

	if (stream.is_open()) {
		std::string line="";
		while (std::getline(stream, line)) {
			buffer.push_back(std::make_shared<Line>(line, tab));
		}
	}
	else {
		buffer.push_back(std::make_shared<Line>("", tab)); //append a single blank file
	}
	stream.close();
}

int File::lines() {
	return buffer.size();
}

std::string File::rawLine(int n) {
	return buffer[n]->getRaw();
}

std::string File::line(int n) {
	return buffer[n]->get();
}

int File::linesize(int n) {
	return buffer[n]->size();
}

std::string File::insert(int c, int x, int y) {
	//insert char at x pos then return it
	return buffer[y]->insert(c, x);
}

int File::decode(int x, int y) {
	return buffer[y]->decode(x);
}

void File::newline(int x, int y) {
	//used to insert a new line buffer
	std::vector<std::shared_ptr<Line>>::iterator it=buffer.begin();

	std::string indent=getIndent(y);
	if (x<(int)indent.length()) {
		indent=indent.substr(0, x);
	}

	//add new line
	buffer.insert(
		it+y+1,
		std::make_shared<Line>(
			indent+
			buffer[y]->substr(x),
			tabsize
		)
	);

	//updates old line
	buffer[y]=std::make_shared<Line>(buffer[y]->substr(0, x), tabsize);
}

void File::delline(int y) {
	buffer[y-1]=std::make_shared<Line>(buffer[y-1]->getRaw()+buffer[y]->getRaw(), tabsize);

	//remove line that cursor was
	buffer.erase(buffer.begin()+y);
}

std::string File::getIndent(int n) {
	std::string tmp=rawLine(n);
	int i=0;

	for (;i<(int)tmp.length();) {
		if (tmp[i]==' '||tmp[i]=='\t') i++;
		else break;
	}
	return tmp.substr(0, i);
}


void File::save() {
	saveas(filename);
}

void File::saveas(std::string fn) {
	filename=fn; //saveas also sets the filename for files saved with "save" later on

	stream.open(fn, std::ios::out);

	for (int i=0;i<(int)buffer.size();i++) {
		stream << buffer[i]->getRaw();

		//add newlines to all lines except for last line
		if (i<(int)buffer.size()-1) {
			stream << "\n";
		}
	}
	//if last line isnt empty and eol is true, and another newline
	if (eol&&buffer[buffer.size()-1]->getRaw()!="") stream << "\n";

	stream.close();
}

std::string File::getfn() {
	return filename;
}