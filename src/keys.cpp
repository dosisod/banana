#include "keys.hpp"

namespace key {
	bool enter(int c) { return (c=='\n'||c==KEY_ENTER); }
	bool backspace(int c) { return (c==127||c==KEY_BACKSPACE); }
	bool home(int c) { return c==KEY_HOME; }
	bool del(int c) { return c==KEY_DC; }
	bool end(int c) { return c==KEY_END; }
	bool up(int c) { return c==KEY_UP; }
	bool down(int c) { return c==KEY_DOWN; }
	bool left(int c) { return c==KEY_LEFT; }
	bool right(int c) { return c==KEY_RIGHT; }
	bool escape(int c) { return c==27; }

	bool bracketLeft(char c) { return (c=='('||c=='['||c=='{'||c=='\''||c=='\"'); }
	bool bracketRight(char c) { return (c==')'||c==']'||c=='}'||c=='\''||c=='\"'); }
	bool bracket(char c) { return (bracketLeft(c)||bracketRight(c)); }

	char bracketize(char b) {
		if (b=='(') return ')';
		else if (b==')') return '(';
		else if (b=='[') return ']';
		else if (b==']') return '[';
		else if (b=='{') return '}';
		else if (b=='}') return '{';
		else if (b=='\"') return '\"';
		else if (b=='\'') return '\'';
		else return 0;
	}

	bool valid(int c) {
		return (
			c<128||
			enter(c)||
			backspace(c)||
			home(c)||
			del(c)||
			end(c)||
			up(c)||
			down(c)||
			left(c)||
			right(c)||
			escape(c)
		);
	}
}