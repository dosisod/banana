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
	else {
		buffer.push_back(new Line("")); //append a single blank file
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
	return buffer[n]->size();
}

std::string File::insert(int c, int x, int y) {
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

void File::delline(int y) {
	buffer[y-1]=new Line(buffer[y-1]->get()+buffer[y]->get());

	//remove line that cursor was
	buffer.erase(buffer.begin()+y);
}

void File::save() {
	saveas(filename);
}

void File::saveas(std::string fn) {
	stream.open(fn, std::ios::out);

	for (auto i:buffer) {
		stream << i->getRaw() << "\n";
	}

	stream.close();
}