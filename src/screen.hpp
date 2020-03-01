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

	void pause() const;

	void parseKey(int c);
	void parseKeys(std::vector<int> c);

	void render();

	//render starting with file line "fy" at terminal line "ty"
	void render(int fy, int ty);

	void home();
	void setxy(int x, int y);
	void delta(int dx, int dy);

	char charCurrent() const;
	char charAt(int x, int y) const;
	char charOver(int x, int y) const;

	//open new file buffer
	void useBuffer(std::shared_ptr<File> f);

	//replace current buffer with file "fn"
	void useBuffer(std::string fn);

	std::shared_ptr<File> file;

	//cursor x and y
	int currx=0;
	int curry=0;

	//y position relative to start of file
	int realy() const;

private:
	std::shared_ptr<Terminal> terminal;

	//line in file to start rendering from
	int filey=0;

	//page up/down will move by N lines at a time
	const int page=10;

	int ruler;
	const int tabsize=4;

	const bool wordwrap=false;

	//decodes cursor position when there are tabs
	int decode() const;
	int decode(int x, int y) const;

	//find what the cursor position should be for a given string
	int encode(std::string s) const;
};