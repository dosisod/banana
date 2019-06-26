#ifndef __KEYS_HPP__
#define __KEYS_HPP__

#include <ncurses.h>

//maps keys that go by many possible values to one function
namespace key {
	bool enter(int c);
	bool backspace(int c);
	bool del(int c); //delete is a keyword
	bool home(int c);
	bool end(int c);
	bool up(int c);
	bool down(int c);
	bool left(int c);
	bool right(int c);
	bool escape(int c);

	bool bracketLeft(char c);
	bool bracketRight(char c);
	bool bracket(char c); //true if c is a left/right bracket

	char bracketize(char b); //get other bracket for given bracket, or zero

	bool valid(int c); //true if key isnt a control key
}

#endif