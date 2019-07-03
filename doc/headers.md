Below is a list of stripped headers for quick reference

Keep in mind that these headers may be a few commits behind

## `Commander` Class

`Commander(std::vector<std::shared_ptr<Command>> c);`

`const typedef std::pair<std::string, std::string> params;`

`params parse(std::string str);`

`void run(std::string str);`

`std::vector<std::shared_ptr<Command>> commands;`

## `Command` Class

`Command(std::string c, std::function<void(std::string)> f);`

`Command(std::string c, std::function<void()> f);`

`bool check(std::string s);`

`void run(std::string s);`

`std::vector<std::string> calls;`

`std::function<void(std::string)> func;`

## `File` Class

`File(std::string fn, int tab);`

`int lines();`

`std::string line(int n);`

`std::string rawLine(int n);`

`int linesize(int n);`

`std::string insert(int c, int x, int y);`

`std::string insert(std::string s, int x, int y);`

`int decode(int x, int y);`

`void newline(int x, int y);`

`void delline(int y);`

`std::string getIndent(int n);`

`void save();`

`void saveas(std::string fn);`

`std::string getfn();`

`std::string filename;`

`std::fstream stream;`

`std::vector<std::shared_ptr<Line>> buffer;`

`bool eol;`

`int tabsize;`

## `key` Namespace

`bool enter(int c);`

`bool backspace(int c);`

`bool del(int c);`

`bool home(int c);`

`bool end(int c);`

`bool up(int c);`

`bool down(int c);`

`bool left(int c);`

`bool right(int c);`

`bool escape(int c);`

`bool bracketLeft(char c);`

`bool bracketRight(char c);`

`bool bracket(char c);`

`char bracketize(char b);`

`bool valid(int c);`

## `Line` Class

`Line(std::string str, int tab);`

`std::string insert(int c, int x);`

`std::string insert(std::string s, int x);`

`std::string get();`

`std::string getRaw();`

`std::string substr(int s);`

`std::string substr(int s, int e);`

`int size();`

`int decode(int x);`

`std::string str;`

`int tabsize;`

## `Screen` Class

`Screen(std::shared_ptr<Terminal> t, int tab);`

`~Screen();`

`void pause();`

`void parseKey(int c);`

`void parseKeys(std::vector<int> c);`

`void render();`

`void render(int fy, int ty);`

`void home();`

`void setxy(int x, int y);`

`void delta(int dx, int dy);`

`char charCurrent();`

`char charAt(int x, int y);`

`char charOver(int x, int y);`

`void useBuffer(std::shared_ptr<File> f);`

`void useBuffer(std::string fn);`

`std::shared_ptr<File> file;`

`int currx;`

`int curry;`

`int realy();`

`std::shared_ptr<Terminal> term;`

`int filey;`

`int ruler;`

`int tabsize;`

`bool wordwrap;`

`int decode();`

`int decode(int x, int y);`

`int encode(std::string s);`

## `ScreenMaster` Class

`ScreenMaster(std::shared_ptr<Terminal> t);`

`~ScreenMaster();`

`void addBuffer(std::string s);`

`void parseKey(int c);`

`void pause();`

`std::shared_ptr<Screen> operator->();`

`std::shared_ptr<Screen> screen();`

`int screenid();`

`int parsenum(std::string s, int d);`

`std::shared_ptr<Terminal> term;`

`std::vector<std::shared_ptr<Screen>> screens;`

`int currentscr;`

`void super();`

`void superParse(int c);`

`std::shared_ptr<Line> superLine;`

`int superx;`

`int tabsize;`

`std::shared_ptr<Commander> commands;`

`std::vector<int> mn_keys;`

## `Terminal` Class

`Terminal();`

`void write(std::string s);`

`void clear(int y);`

`void zero(int y, std::string s);`

`void update();`

`void move(int x, int y);`

`int getx();`

`int gety();`

`WINDOW* window;`

`int x;`

`int y;`