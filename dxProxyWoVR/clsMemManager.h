#pragma once
#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>

#include <string>
#include <map>
#include <psapi.h>

class clsMemManager
{
private:
	DWORD pid;
	HWND hWnd;
	HANDLE hProcess;
	bool attached;
	std::map<std::string, DWORD> moduleList;

public:
	clsMemManager();
	bool attachWindow(char*);
	bool attachWindow(HWND);
	void closeProcess();
	bool isConnected();
	DWORD getPID();
	DWORD getDLLAddress(char*);
	HWND getHWND();
	void listModules();
	int readMemoryL(DWORD, int);
	float readMemoryF(DWORD);
	double readMemoryD(DWORD);
	void writeMemoryL(DWORD, int, int);
	void writeMemoryF(DWORD, float);
	void writeMemoryD(DWORD, double);
	void writeMemoryS(DWORD, int, BYTE[]);
};
