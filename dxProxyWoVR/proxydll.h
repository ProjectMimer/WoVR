#pragma once

#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d9.h>
#include <sstream>
#include <fstream>
#include "cIDirect3D9.h"
#include "cIDirect3DDevice9.h"

#define DllExport __declspec(dllexport)
#define DllImport __declspec(dllimport)

bool HasErrors();
std::string GetErrors();
void PrintErrors();