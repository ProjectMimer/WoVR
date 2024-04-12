#include "clsMemManager.h"
#include <tlhelp32.h>

clsMemManager::clsMemManager() : pid(0), hWnd(0), hProcess(0), attached(0)
{
	return;
}

bool clsMemManager::attachWindow(char* windowName) {
	if (pid == 0) {
		hWnd = FindWindow(NULL, windowName);
		return attachWindow(hWnd);
	}
	else {
		attached = FALSE;
	}
	return attached;
}

bool clsMemManager::attachWindow(HWND thWnd) {
	if (pid == 0) {
		hWnd = thWnd;
		if (hWnd) {
			GetWindowThreadProcessId(hWnd, &pid);
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
			listModules();
			attached = TRUE;
		}
		else {
			attached = FALSE;
		}
	}
	else {
		attached = FALSE;
	}
	return attached;
}

void clsMemManager::closeProcess() {
	if (hProcess != 0) {
		CloseHandle(hProcess);
	}
	moduleList.clear();
	pid = 0;
	hWnd = 0;
	hProcess = 0;
	attached = 0;
	return;
}

bool clsMemManager::isConnected() {
	return attached;
}

DWORD clsMemManager::getPID() {
	return pid;
}

HWND clsMemManager::getHWND() {
	return hWnd;
}

DWORD clsMemManager::getDLLAddress(char* moduleName) {
	std::string toFind(moduleName);
	std::map<std::string, DWORD>::iterator it = moduleList.begin();
	for (it = moduleList.begin(); it != moduleList.end(); ++it) {
		//std::string output(it->first);
		//MessageBox(NULL, (LPCSTR)output.c_str(), "DLL List", 0);
		if (it->first == toFind) {
			return it->second;
		}
	}
	return 0;
}

void clsMemManager::listModules() {
	HMODULE hMods[1024];
	DWORD cbNeeded;

	moduleList.clear();
	if (EnumProcessModulesEx(hProcess, hMods, sizeof(hMods), &cbNeeded, LIST_MODULES_ALL)) {
		for (int i = 0; i < (int)(cbNeeded / sizeof(HMODULE)); i++) {
			char szModName[MAX_PATH];
			if (GetModuleBaseName(hProcess, hMods[i], szModName, MAX_PATH)) {
				moduleList.insert(std::make_pair<std::string, DWORD>(std::string(szModName), (DWORD)hMods[i]));
			}
		}
	}
	return;
}

int clsMemManager::readMemoryL(DWORD address, int readSize) {
	int retVal = 0;
	ReadProcessMemory(hProcess, (PVOID)address, &retVal, readSize, 0);
	return retVal;
}

float clsMemManager::readMemoryF(DWORD address) {
	float retVal = 0.0;
	ReadProcessMemory(hProcess, (PVOID)address, &retVal, 4, 0);
	return retVal;
}

double clsMemManager::readMemoryD(DWORD address) {
	double retVal = 0.0;
	ReadProcessMemory(hProcess, (PVOID)address, &retVal, 8, 0);
	return retVal;
}

void clsMemManager::writeMemoryL(DWORD address, int writeSize, int writeVal) {
	WriteProcessMemory(hProcess, (PVOID)address, &writeVal, writeSize, 0);
	return;
}

void clsMemManager::writeMemoryF(DWORD address, float writeVal) {
	WriteProcessMemory(hProcess, (PVOID)address, &writeVal, 4, 0);
	return;
}

void clsMemManager::writeMemoryD(DWORD address, double writeVal) {
	WriteProcessMemory(hProcess, (PVOID)address, &writeVal, 8, 0);
	return;
}

void clsMemManager::writeMemoryS(DWORD address, int writeSize, BYTE writeVal[]) {
	WriteProcessMemory(hProcess, (PVOID)address, writeVal, writeSize, 0);
	return;
}
