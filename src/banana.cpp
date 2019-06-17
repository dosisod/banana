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
	else {
		for (int i=1;i<argc;i++) {
			master.addBuffer(argv[i]);
		}
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