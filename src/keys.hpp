#include <ncurses.h>

//maps keys that go by many possible values to one function
namespace key {
	bool enter(int c) { return (c=='\n'||c==KEY_ENTER); }
	bool backspace(int c) { return (c==127||c==KEY_BACKSPACE); }
	bool home(int c) { return c==KEY_HOME; }
	bool end(int c) { return c==KEY_END; }
	bool up(int c) { return c==KEY_UP; }
	bool down(int c) { return c==KEY_DOWN; }
	bool left(int c) { return c==KEY_LEFT; }
	bool right(int c) { return c==KEY_RIGHT; }
	bool escape(int c) { return c==27; }
}