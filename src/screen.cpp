#include <vector>
#include <string>

#include "commander.hpp"
#include "command.hpp"
#include "screen.hpp"
#include "keys.hpp"

//This file contains constructor, destructor, and super mode functions

Screen::Screen() {
	setlocale(LC_ALL, ""); //allow for unicode
	window=initscr(); //init and clear screen
	start_color();
	noecho(); //dont print characters to screen

	keypad(window, true); //allows arrow keys to be detected
	ESCDELAY=0;

	update();
	refresh();

	//setup colors
	init_pair(1, COLOR_BLACK, COLOR_YELLOW);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_BLACK, COLOR_WHITE);

	commands=std::make_shared<Commander>(std::vector<std::shared_ptr<Command>>({
		std::make_shared<Command>(
			"save s", [=](std::string s) {
				file->save();
			}),
		std::make_shared<Command>(
			"saveas sa", [=](std::string s) {
				file->saveas(s);
			}),
		std::make_shared<Command>(
			"quit exit q", [=](std::string s) {
				this->~Screen(); //calls deconstructor then quits
				exit(0);
			}),
		std::make_shared<Command>( //save under same name then exit
			"quitsave exitsave qs", [=](std::string s) {
				file->save();
				this->~Screen();
				exit(0);
			}),
		std::make_shared<Command>( //save under different name then exit
			"quitas exitas qa", [=](std::string s) {
				file->saveas(s);
				this->~Screen();
				exit(0);
			})
		})
	);
}

Screen::~Screen() {
	endwin();
}

void Screen::super() {
	isSuper=true;

	//clear from last time super was active
	superx=0;
	superLine=std::make_shared<Line>("");

	render(0,1); //move all lines down one

	wmove(window, 0, 0);
	attron(COLOR_PAIR(3));
	write(std::string(termx, ' ')); //fill line with white space
	wmove(window, 0, 0);

	int c=getch();
	while (!key::escape(c)&&!key::enter(c)) {
		wmove(window, 0, 0); //goto start of line
		write(std::string(termx, ' ')); //fill line with white space
		wmove(window, 0, 0); //go back to start of line

		parseKey(c); //parse key press
		write(superLine->get()); //write line
		wmove(window, 0, superx); //move cursor back to correct position

		c=getch();
	}
	if (key::enter(c)) commands->parse(superLine->getRaw());

	isSuper=false;
}