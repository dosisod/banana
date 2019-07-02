#include "screenMaster.hpp"
#include "keys.hpp"

ScreenMaster::ScreenMaster(std::shared_ptr<Terminal> t) {
	term=t;

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
				if (screens.size()>1) { //calls deconstructor then quits
					screens.erase(screens.begin()+currentscr);

					if (currentscr>=(int)screens.size()) currentscr--;
				}
				else {
					this->~ScreenMaster();
					exit(0);
				}
			}),
		std::make_shared<Command>( //save under same name then exit
			"quitsave exitsave qs", [=]() {
				screen()->file->save();
				this->commands->run("quit");
			}),
		std::make_shared<Command>( //save under different name then exit
			"quitas exitas qa", [=](std::string s) {
				screen()->file->saveas(s);
				this->commands->run("quit");
			}),
		std::make_shared<Command>( //open another file in same buffer
			"open o", [=](std::string s) {
				screen()->useBuffer(s);
				screen()->home();
			}),
		std::make_shared<Command>( //open help
			"help h", [=]() {
				addBuffer("help.md");
				screen()->home();
			}),
		std::make_shared<Command>( //open another file in new buffer
			"tabnew tn", [=](std::string s) {
				addBuffer(s);
				screen()->home();
			}),
		std::make_shared<Command>( //change tab
			"tab t", [=](std::string s) {
				int tab=parsenum(s, screenid());

				if (tab>0&&tab<=(int)screens.size()) {
					currentscr=tab-1; //tab starts at 1
					screen()->render();
				}
			}),
		std::make_shared<Command>( //move over N tabs
			"tabdelta td", [=](std::string s) {
				int tab=parsenum(s, screenid());
				this->commands->run("tab "+std::to_string(screenid()+tab+1));
			}),
		std::make_shared<Command>( //records a new macro
			"macronew mn", [=]() {
				term->zero(0, "RECORDING");

				mn_keys.clear();
				int current=getch();

				while (!key::escape(current)) {
					mn_keys.emplace_back(current); //keep adding characters until escape is pressed
					current=getch();
				}
			}),
		std::make_shared<Command>( //replays stored macro
			"macroreplay mr", [=]() {
				term->zero(0, "REPLAYING");

				int current;
				do {
					screen()->parseKeys(mn_keys);
					screen()->render(0, 1);
					current=getch();
				} while (key::enter(current));
			}),
		std::make_shared<Command>( //duplicate current line
			"duplicate dupe d", [=]() {
				term->zero(0, "DUPLICATING");

				int current;
				std::string line=screen()->file->rawLine(screen()->curry);

				do {
					screen()->file->newline( //add blank line under current line
						line.length(),
						screen()->curry
					);

					screen()->file->insert( //duplicate line above into blank space
						line,
						0,
						screen()->curry+1
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

std::shared_ptr<Screen> ScreenMaster::operator->() {
	return screen();
}

std::shared_ptr<Screen> ScreenMaster::screen() {
	return screens[currentscr];
}

void ScreenMaster::addBuffer(std::string s) {
	screens.emplace_back(
		std::make_shared<Screen>(term, tabsize)
	);
	currentscr++;
	screens[screens.size()-1]->useBuffer(s);
}

void ScreenMaster::parseKey(int c) {
	if (key::escape(c)) {
		super();
	}
	else {
		screen()->parseKey(c);
	}
}

void ScreenMaster::pause() {
	getch();
}

void ScreenMaster::super() {
	//clear from last time super was active
	superx=0;
	superLine=std::make_shared<Line>("", tabsize);

	screen()->render(0, 1); //move all lines down one

	attron(COLOR_PAIR(3));
	term->clear(0);

	//print file info until a key is pressed
	term->write(" ");

	for (std::vector<Screen>::size_type i=0;i!=screens.size();i++) {
		if ((int)i==currentscr) { //indicates current tab
			term->write(" <"+screens[i]->file->getfn()+">");
		}
		else { //indicates inactive tab
			term->write(" ["+screens[i]->file->getfn()+"]");
		}
	}
	term->move(0, 0);

	int c=getch();
	term->write(std::string(term->getx(), ' ')); //fill line with white space

	while (!key::escape(c)&&!key::enter(c)) {
		term->clear(0);

		superParse(c); //parse key press
		term->write(superLine->get()); //write line
		term->move(superx, 0); //move cursor back to correct position

		c=getch();
	}
	if (key::enter(c)) commands->run(superLine->getRaw());
}

void ScreenMaster::superParse(int c) {
	if (key::del(c)) { //convert delete into a backspace
		if (superx>=superLine->size()) return;
		else superx++; //move over as if it was a backspace

		c=KEY_BACKSPACE;
	}
	if (key::left(c)) {
		if (superx!=0) superx--;
	}
	else if (key::right(c)) {
		if (superx<superLine->size()) superx++;
	}
	else if (key::end(c)) {
		superx=superLine->size();
	}
	else if (key::home(c)) {
		superx=0;
	}
	else {
		//return if an invalid key was pressed
		if (key::down(c)||key::up(c)) return;

		superLine->insert(c, superx);
		if (key::backspace(c)&&superx!=0) superx--;
		else if (!key::backspace(c)) superx++;
	}
}

int ScreenMaster::screenid() {
	return currentscr;
}

int ScreenMaster::parsenum(std::string s, int d) {
	try {
		return std::stoi(s);
	}
	//if number is not a number, return default
	catch (...) {
		return d;
	}
}