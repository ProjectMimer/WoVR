#include "clsKeyboard.h"
#include <iostream>
#include <sstream>

std::set<int> curKeyList;
std::set<int> keyListDown;
std::set<int> keyListUp;
BYTE kbdKeyList[255] = { 0 };

void setKeyDown(BYTE keyToSet, BYTE extend)
{
	if (kbdKeyList[keyToSet] == 0) {
		keybd_event(keyToSet, 0, extend | 0, 0);
		kbdKeyList[keyToSet] = 1;
	}
}

void setKeyUp(BYTE keyToSet, BYTE extend)
{
	keybd_event(keyToSet, 0, extend | KEYEVENTF_KEYUP, 0);
	kbdKeyList[keyToSet] = 0;
}


bool isKeyPressed(int value) {
	return (curKeyList.find(value) != curKeyList.end());
}
bool isKeyDown(int value) {
	return (keyListDown.find(value) != keyListDown.end());
}
bool isKeyUp(int value) {
	return (keyListUp.find(value) != keyListUp.end());
}

void clearKeyboard() {
	curKeyList.clear();
	return;
}

void checkKeyboard() {
	const int KEY_LIST_SIZE = 256;
	BYTE keyList[KEY_LIST_SIZE] = { 0 };

	GetKeyState(0);
	bool status = GetKeyboardState(keyList);

	std::set<int> tmpKeys;

	tmpKeys.clear();
	keyListDown.clear();
	keyListUp.clear();

	for (int i = 0; i < KEY_LIST_SIZE; i++) { if (keyList[i] >= 128) { tmpKeys.insert(i); } }
	std::set_difference(tmpKeys.begin(), tmpKeys.end(), curKeyList.begin(), curKeyList.end(), std::inserter(keyListDown, keyListDown.end()));
	std::set_difference(curKeyList.begin(), curKeyList.end(), tmpKeys.begin(), tmpKeys.end(), std::inserter(keyListUp, keyListUp.end()));

	curKeyList.clear();
	std::copy(tmpKeys.begin(), tmpKeys.end(), std::inserter(curKeyList, curKeyList.end()));

	return;
}

void debugKeys(int keyLists) {
	std::stringstream outStream;
	if (keyLists == 1 && curKeyList.size() > 0) {
		outStream << "CurrKeyList:";
		for (std::set<int>::iterator inner = curKeyList.begin(); inner != curKeyList.end(); ++inner) {
			outStream << *inner << ",";
		}
		outStream << "\n";
	}

	if (keyLists == 2 && keyListDown.size() > 0) {
		outStream << "KeyListDown:";
		for (std::set<int>::iterator inner = keyListDown.begin(); inner != keyListDown.end(); ++inner) {
			outStream << *inner << ",";
		}
		outStream << "\n";
	}

	if (keyLists == 4 && keyListUp.size() > 0) {
		outStream << "KeyListUp:";
		for (std::set<int>::iterator inner = keyListUp.begin(); inner != keyListUp.end(); ++inner) {
			outStream << *inner << ",";
		}
		outStream << "\n";
	}
	OutputDebugString(NULL);
	OutputDebugString(outStream.str().c_str());
	return;
}
