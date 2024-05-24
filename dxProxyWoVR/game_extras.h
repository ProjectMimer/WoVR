#pragma once

#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d9.h>
#include <DirectXMath.h>
#include <list>
#include <iostream>
#include <fstream>

#include "detours.h"
#include "stDX11.h"
#include "simpleVR.h"
#include "stBasicTexture.h"
//#include "simpleXR.h"

using namespace DirectX;

#define DllExport __declspec(dllexport)
#define DllImport __declspec(dllimport)

void InitDetours(HANDLE hModule);
void ExitDetours();