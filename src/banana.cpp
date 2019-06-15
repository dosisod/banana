#include <string>
#include <memory>

#include "terminal.hpp"
#include "screen.hpp"

int main (int argc, char *argv[]) {
	std::shared_ptr<Terminal> term=std::make_shared<Terminal>();
	Screen screen { term };

	if (argc==1) {
		screen.useBuffer(
			std::make_shared<File>("")
		);
	}
	else if (argc==2) {
		screen.useBuffer(
			std::make_shared<File>(std::string(argv[1]))
		);
	}
	else {
		term->write("banana takes exactly 1 or 0 parameters (for now)\n");
		screen.pause();

		return 1;
	}

	screen.render();
	screen.home();

	do {
		screen.parseKey(getch());
		screen.render();
	} while (true);

	screen.pause();

	return 0;
}