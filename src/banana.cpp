#include <string>
#include <memory>

#include "screenMaster.hpp"
#include "terminal.hpp"

int main (int argc, char *argv[]) {
	std::shared_ptr<Terminal> term=std::make_shared<Terminal>();
	ScreenMaster master { term };

	if (argc==1) {
		master.addBuffer("");
	}
	else if (argc==2) {
		master.addBuffer(std::string(argv[1]));
	}
	else {
		term->write("banana takes exactly 1 or 0 parameters (for now)\n");
		master.pause();

		return 1;
	}

	master->render();
	master->home();

	do {
		master.parseKey(getch());
		master->render();
	} while (true);

	master.pause();

	return 0;
}