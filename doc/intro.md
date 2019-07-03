# Introduction

banana is built to be small, yet easy to use, modify, and scale up

Many basic features that you may expect are included, such as automatic bracket opening/closing/indenting and line indenting

To get access to `CONTROL+KEY`-like functionality, there is super mode (activated using `ESCAPE`)

This mode is similar in nature to VIM, requiring commands to be used to manipulate the data (for the most part)

For a list of commands, see the [help](/help.md) page

## Design

banana follows a simple design structure:

```
ScreenMaster
|
| Line //line specificaly for super-mode
|
| Commander
| |
| | Commands //vector of command objects
|
| Screens //vector of type screen (AKA tabs)
| |
| | File
| | |
| | | Lines //vector of type line
```

For a complete list of headers, click [here][headers.md]

`ScreenMaster` controls the virtual `Screen`s, data going from the user, commands, and data being displayed to the physical screen

`Commander` handles command inputs, checks what inputs call what commands, and can run commands

`Command` objects contain a single lambda function and a string of valid calls to that lambda

Each `Screen` holds an independently controlled cursor position and `File` buffer

`File` objects control multiple `Line`s. This is the object that actually stores the data being edited, and can save/oven files as needed

`Line`s are the smallest "unit": they are very simple, but very useful when manipulating data