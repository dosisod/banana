#include "screenMaster.hpp"
#include "keys.hpp"

ScreenMaster::ScreenMaster(std::shared_ptr<Terminal> t) {
	term=t;

	commands=std::make_shared<Commander>(std::vector<std::shared_ptr<Command>>({
		std::make_shared<Command>(
			"save s", [=](std::string s) {
				screen()->file->save();
			}),
		std::make_shared<Command>(
			"saveas sa", [=](std::string s) {
				screen()->file->saveas(s);
			}),
		std::make_shared<Command>(
			"quit exit q", [=](std::string s) {
				this->~ScreenMaster(); //calls deconstructor then quits
				exit(0);
			}),
		std::make_shared<Command>( //save under same name then exit
			"quitsave exitsave qs", [=](std::string s) {
				screen()->file->save();
				this->~ScreenMaster();
				exit(0);
			}),
		std::make_shared<Command>( //save under different name then exit
			"quitas exitas qa", [=](std::string s) {
				screen()->file->saveas(s);
				this->~ScreenMaster();
				exit(0);
			}),
		std::make_shared<Command>( //open another file in same buffer
			"open o", [=](std::string s) {
				screen()->useBuffer(
					std::make_shared<File>(s)
				);
				screen()->home();
			}),
		std::make_shared<Command>( //open another file in same buffer
			"tabnew tn", [=](std::string s) {
				addBuffer(s);
				screen()->home();
			}),
		std::make_shared<Command>( //open another file in same buffer
			"tab t", [=](std::string s) {
				try {
					int input=std::stoi(s);

					//valid tab number was entered
					if (input>0&&input<=(int)screens.size()) {
						currentscr=input-1; //tab starts at 1
						screen()->render();
					}
				}
				//if number is not a number, pass
				catch (...) {}
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
		std::make_shared<Screen>(term)
	);
	currentscr++;
	screens[screens.size()-1]->useBuffer(std::make_shared<File>(s));
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
	isSuper=true;

	//clear from last time super was active
	superx=0;
	superLine=std::make_shared<Line>("");

	screen()->render(0, 1); //move all lines down one

	term->move(0, 0);
	attron(COLOR_PAIR(3));
	term->write(std::string(term->getx(), ' ')); //fill line with white space
	term->move(0, 0);

	//print file info until a key is pressed
	term->write(" ");

	for (std::vector<Screen>::size_type i=0;i!=screens.size();i++) {
		if ((int)i==currentscr) { //indicates current tab
			term->write(" "+screens[i]->file->getfn());
		}
		else {
			term->write(" ["+screens[i]->file->getfn()+"]");
		}
	}
	term->move(0, 0);

	int c=getch();
	term->write(std::string(term->getx(), ' ')); //fill line with white space

	while (!key::escape(c)&&!key::enter(c)) {
		term->move(0, 0); //goto start of line
		term->write(std::string(term->getx(), ' ')); //fill line with white space
		term->move(0, 0); //go back to start of line

		superParse(c); //parse key press
		term->write(superLine->get()); //write line
		term->move(superx, 0); //move cursor back to correct position

		c=getch();
	}
	if (key::enter(c)) commands->parse(superLine->getRaw());

	isSuper=false;
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