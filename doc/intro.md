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

`TBD`