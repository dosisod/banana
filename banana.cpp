#include <string>

#include "file.hpp"
#include "screen.hpp"

int main (int argc, char *argv[]) {
	Screen screen;

	if (argc!=2) {
		screen.write("banana takes exactly 1 parameter (for now)\n");
	}

	File f(std::string(argv[1]));

	screen.pause();

	return 0;
}