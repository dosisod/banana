#pragma once

#include <ncurses.h>

//helper functions to parse key info
namespace key {

bool enter(int c);
bool backspace(int c);
bool del(int c); //delete is a keyword
bool home(int c);
bool end(int c);
bool up(int c);
bool down(int c);
bool pageup(int c);
bool pagedown(int c);
bool left(int c);
bool right(int c);
bool escape(int c);

bool bracketLeft(char c);
bool bracketRight(char c);
bool bracket(char c);

//get other bracket for given bracket, or zero
char bracketize(char b);

bool valid(int c);

}