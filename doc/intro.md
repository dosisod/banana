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

`Commander::Commander(std::vector<std::shared_ptr<Command>> c)`

`void Commander::parse(std::string str)`

`std::vector<std::shared_ptr<Command>> Commander::commands`

## `Command` Class

`Command::Command(std::string c, std::function<void(std::string)> f)`

`bool Command::check(std::string s)`

`void Command::run(std::string s)`

`std::vector<std::string> Command::calls`

`std::function<void(std::string)> Command::func`

## `File` Class

`File::File(std::string fn)`

`int File::lines()`

`std::string File::line(int n)`

`int File::linesize(int n)`

`std::string File::insert(int c, int x, int y)`

`void File::newline(int x, int y)`

`void File::delline(int y)`

`void File::save()`

`void File::saveas(std::string fn)`

`std::string File::filename`

`std::fstream File::stream`

`std::vector<std::shared_ptr<Line>> File::buffer`

## `key` Namespace

`bool key::enter(int c)`

`bool key::backspace(int c)`

`bool key::del(int c)`

`bool key::home(int c)`

`bool key::end(int c)`

`bool key::up(int c)`

`bool key::down(int c)`

`bool key::left(int c)`

`bool key::right(int c)`

`bool key::escape(int c)`

## `Line` Class

`Line::Line(std::string str)`

`std::string Line::insert(int c, int x)`

`std::string Line::get()`

`std::string Line::getRaw()`

`int Line::size()`

`std::string Line::str`

`int Line::decode(int x)`

`int Line::tabsize`

## `Screen` Class

`Screen::Screen()`

`Screen::~Screen()`

`void Screen::super()`

`void Screen::pause()`

`void Screen::parseKey(int c)`

`void Screen::parseKeys(std::vector<int> c)`

`void Screen::write(std::string s)`

`void Screen::render()`

`void Screen::render(int fy, int ty)`

`void Screen::home()`

`void Screen::setxy(int x, int y)`

`void Screen::delta(int dx, int dy)`

`void Screen::useBuffer(std::shared_ptr<File> f)`

`WINDOW* Screen::window`

`int Screen::currx`

`int Screen::curry`

`std::shared_ptr<Line> Screen::superLine`

`int Screen::superx`

`int Screen::termx`

`int Screen::termy`

`void Screen::update()`

`std::shared_ptr<File> Screen::file`

`int Screen::ruler`

`bool Screen::wordwrap`

`bool Screen::isSuper`

`std::shared_ptr<Commander> Screen::commands`