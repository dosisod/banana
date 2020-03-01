#include "screenMaster.hpp"
#include "keys.hpp"

ScreenMaster::ScreenMaster(std::shared_ptr<Terminal> terminal) :
	terminal(terminal)
{
	commands=std::make_shared<Commander>(std::vector<std::shared_ptr<Command>>({
		std::make_shared<Command>(
			"save s", [=]() {
				screen()->file->save();
			}),

		std::make_shared<Command>(
			"saveas sa", [=](std::string s) {
				screen()->file->saveas(s);
			}),

		std::make_shared<Command>(
			"quit exit q", [=]() {
				if (screens.size() > 1) {
					screens.erase(screens.begin() + currentscr);

					if (currentscr >= (int)screens.size()) {
						currentscr--;
					}
				}
				else {
					this->~ScreenMaster();
					exit(0);
				}
			}),

		std::make_shared<Command>(
			"quitsave exitsave qs", [=]() {
				screen()->file->save();
				this->commands->run("quit");
			}),

		std::make_shared<Command>(
			"quitas exitas qa", [=](std::string s) {
				screen()->file->saveas(s);
				this->commands->run("quit");
			}),

		std::make_shared<Command>(
			"open o", [=](std::string s) {
				screen()->useBuffer(s);
				screen()->home();
			}),

		std::make_shared<Command>(
			"help h", [=]() {
				addBuffer("help.md");
				screen()->home();
			}),

		std::make_shared<Command>(
			"tabnew tn", [=](std::string s) {
				addBuffer(s);
				screen()->home();
			}),

		std::make_shared<Command>(
			"tab t", [=](std::string s) {
				int tab=parsenum(s, screenid());

				if (tab > 0 && tab <= (int)screens.size()) {
					currentscr=tab - 1;
					screen()->render();
				}
			}),

		std::make_shared<Command>(
			"tabdelta td", [=](std::string s) {
				int tab=parsenum(s, screenid());
				this->commands->run(
					"tab " +
					std::to_string(screenid() + tab + 1)
				);
			}),

		std::make_shared<Command>(
			"macronew mn", [=]() {
				terminal->zero(0, "RECORDING");

				mn_keys.clear();
				int current=getch();

				while (!key::escape(current)) {
					mn_keys.emplace_back(current);
					current=getch();
				}
			}),

		std::make_shared<Command>(
			"macroreplay mr", [=]() {
				terminal->zero(0, "REPLAYING");

				int current;
				do {
					screen()->parseKeys(mn_keys);
					screen()->render(0, 1);

					attron(COLOR_PAIR(3));
					terminal->zero(0, "REPLAYING");

					current=getch();
				} while (key::enter(current));
			}),

		std::make_shared<Command>(
			"duplicate dupe d", [=]() {
				terminal->zero(0, "DUPLICATING");

				int current;
				std::string line=screen()->file->rawLine(screen()->curry);

				do {
					//add blank line under current line
					screen()->file->newline(
						line.length(),
						screen()->curry
					);

					//duplicate line above into blank space
					screen()->file->insert(
						line,
						0,
						screen()->curry + 1
					);

					screen()->render(0, 1);
					current=getch();
				} while (key::enter(current));
			})
		})
	);
}

ScreenMaster::~ScreenMaster() {
	endwin();
}

std::shared_ptr<Screen> ScreenMaster::operator->() const {
	return screen();
}

std::shared_ptr<Screen> ScreenMaster::screen() const {
	return screens[currentscr];
}

void ScreenMaster::addBuffer(std::string str) {
	screens.emplace_back(
		std::make_shared<Screen>(terminal, tabsize)
	);

	currentscr++;
	screens[screens.size() - 1]->useBuffer(str);
}

void ScreenMaster::parseKey(int c) {
	if (key::escape(c)) {
		super();
	}
	else {
		screen()->parseKey(c);
	}
}

void ScreenMaster::pause() const {
	getch();
}

void ScreenMaster::super() {
	superx=0;
	superLine=std::make_shared<Line>("", tabsize);

	//move all lines down one
	screen()->render(0, 1);

	attron(COLOR_PAIR(3));
	terminal->clear(0);

	terminal->write(" ");

	for (std::vector<Screen>::size_type i=0 ; i!=screens.size() ; i++) {
		if ((int)i == currentscr) {
			//indicates current tab
			terminal->write(
				" <" +
				screens[i]->file->getfn() +
				">"
			);
		}
		else {
			//indicates inactive tab
			terminal->write(
				" [" +
				screens[i]->file->getfn() +
				"]"
			);
		}
	}
	terminal->move(0, 0);

	int c=getch();

	terminal->write(std::string(terminal->getx(), ' '));

	while (!key::escape(c) && !key::enter(c)) {
		terminal->clear(0);

		superParse(c);

		terminal->write(superLine->get());

		//move cursor back to correct position
		terminal->move(superx, 0);

		c=getch();
	}
	if (key::enter(c)) {
		commands->run(superLine->getRaw());
	}
}

void ScreenMaster::superParse(int c) {
	if (key::del(c)) {
		if (superx >= superLine->size()) {
			return;
		}
		else {
			//move over as if it was a backspace
			superx++;
		}

		c=KEY_BACKSPACE;
	}
	if (key::left(c)) {
		if (superx!=0) {
			superx--;
		}
	}
	else if (key::right(c)) {
		if (superx < superLine->size()) {
			superx++;
		}
	}
	else if (key::end(c)) {
		superx=superLine->size();
	}
	else if (key::home(c)) {
		superx=0;
	}
	else {
		if (key::down(c) || key::up(c)) {
			return;
		}

		superLine->insert(c, superx);

		if (key::backspace(c) && superx!=0) {
			superx--;
		}
		else if (!key::backspace(c)) {
			superx++;
		}
	}
}

int ScreenMaster::screenid() const {
	return currentscr;
}

int ScreenMaster::parsenum(std::string str, int fail) {
	try {
		return std::stoi(str);
	}
	catch (...) {
		return fail;
	}
}