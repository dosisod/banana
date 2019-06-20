# Introduction

This doc will explain many of the core design layouts and structures of the project

Included is a structure diagram and complete headers list with link to docs+sources

# Structure

```
banana
//main file
|
|    Screen
|    //acts as the main "file" to "screen" interface
|    //handles all displaying, parsing and rendering
|    |
|    |    Line (for super line aka command mode)
|    |    //allows for parsing of text while inputing commands
|    |    |
|    |    |    string (holds content of line)
|    |    |    parsing methods etc (manipulating string)
|    |
|    |
|    |    File (pointer)
|    |    //stores current file buffer
|    |    //tells screen what file it needs to be editing/parsing
|    |    //screen does not have direct access to file, but can manipulate it
|    |    |
|    |    |    Vector (vector of Lines)
|    |    |    //allows for easy manipulation of strings in the file
|    |    |    |
|    |    |    |    Line
|    |    |    |    |
|    |    |    |    | same as above Line class
|    |    |
|    |    |
|    |    |    functions (merging/splitting lines, saving etc)
|    |
|    |
|    |    Commander
|    |    //takes input and determines what Command needs to be called
|    |    |
|    |    |    Vector (of Commands)
|    |    |    //allows adding and deleting of commands
|    |    |    |
|    |    |    |    Command
|    |    |    |    //single lambda with space-seperated string of valid "calls"
|    |    |    |    //lambda can access important functions even after instantiation
|    |    |    |    |
|    |    |    |    | vector of strings (contining valid "calls")
|    |    |    |    | lambda of a function to call when triggered
|    |    |    |    | funciton to check whether to trigger lambda
|    |    |
|    |    |
|    |    |    functions (parsing string and calling appropriate funcition)
```

This is a concise diagram, showing how classes are organized in the hierarchy

For more details on how a class, function, or variable is intended to be used, refer to the header list below

# All Headers

Below is a list of stripped headers for quick reference

## `Commander` Class

`Commander(std::vector<std::shared_ptr<Command>> c);`

`const typedef std::pair<std::string, std::string> params;`

`params parse(std::string str);`

`void run(std::string str);`

`std::vector<std::shared_ptr<Command>> commands;`

## `Command` Class

`Command(std::string c, std::function<void(std::string)> f);`

`bool check(std::string s);`

`void run(std::string s);`

`std::vector<std::string> calls;`

`std::function<void(std::string)> func;`

## `File` Class

`File(std::string fn, int tab);`

`int lines();`

`std::string line(int n);`

`int linesize(int n);`

`std::string insert(int c, int x, int y);`

`void newline(int x, int y);`

`void delline(int y);`

`void save();`

`void saveas(std::string fn);`

`std::string getfn();`

`std::string filename;`

`std::fstream stream;`

`std::vector<std::shared_ptr<Line>> buffer;`

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

## `Line` Class

`Line(std::string str, int tab);`

`std::string insert(int c, int x);`

`std::string get();`

`std::string getRaw();`

`int size();`

`std::string str;`

`int decode(int x);`

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

`void useBuffer(std::shared_ptr<File> f);`

`std::shared_ptr<File> file;`

`std::shared_ptr<Terminal> term;`

`int currx;`

`int curry;`

`int ruler;`

`int tabsize;`

`bool wordwrap;`

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

`bool isSuper;`

`int tabsize;`

`std::shared_ptr<Commander> commands;`

## `Terminal` Class

`Terminal();`

`void write(std::string s);`

`void update();`

`void move(int x, int y);`

`int getx();`

`int gety();`

`WINDOW* window;`

`int x;`

`int y;`