#pragma once

#include <ncurses.h>
#include <vector>
#include <string>
#include <memory>

#include "commander.hpp"
#include "terminal.hpp"
#include "file.hpp"

class Screen {
public:
	Screen(std::shared_ptr<Terminal> terminal, int tabsize);
	~Screen();

	void pause();

	void parseKey(int c);
	void parseKeys(std::vector<int> c);

	void render();

	//render starting with file line "fy" at terminal line "ty"
	void render(int fy, int ty);

	void home();
	void setxy(int x, int y);
	void delta(int dx, int dy);

	char charCurrent();
	char charAt(int x, int y);
	char charOver(int x, int y);

	//open new file buffer
	void useBuffer(std::shared_ptr<File> f);

	//replace current buffer with file "fn"
	void useBuffer(std::string fn);

	std::shared_ptr<File> file;

	//cursor x and y
	int currx=0;
	int curry=0;

	//y position relative to start of file
	int realy();

private:
	std::shared_ptr<Terminal> terminal;

	//line in file to start rendering from
	int filey=0;

	//page up/down will move by N lines at a time
	int page=10;

	int ruler;
	int tabsize=4;

	bool wordwrap=false;

	//decodes cursor position when there are tabs
	int decode();

	int decode(int x, int y);

	//find what the cursor position should be for a given string
	int encode(std::string s);
};