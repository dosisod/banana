#include <string>

#include "screen.hpp"

int main (int argc, char *argv[]) {
	Screen screen;

	if (argc!=2) {
		screen.write("banana takes exactly 1 parameter (for now)\n");
		screen.pause();

		return -1;
	}

	File f { std::string(argv[1]) }; //read file into file buffer
	screen.useBuffer(&f); //set screen to use the file

	screen.render();
	screen.home();

	do {
		screen.listen();
	} while (true);

	screen.pause();

	return 0;
}