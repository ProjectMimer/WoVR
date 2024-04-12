#pragma once
#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>

void setKeyDown(BYTE keyToSet, BYTE extend = 0);
void setKeyUp(BYTE keyToSet, BYTE extend = 0);
bool isKeyPressed(int);
bool isKeyDown(int);
bool isKeyUp(int);
void clearKeyboard();
void checkKeyboard();
void debugKeys(int);
