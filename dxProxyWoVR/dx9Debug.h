#pragma once
#define D3D_DEBUG_INFO

#ifndef DX9_DEBUG
#define DX9_DEBUG

#undef UNICODE
#define WIN32_LEAN_AND_MEAN	
#include <windows.h>
#include <d3d9.h>
#include <string>
#include <vector>


struct rendStat
{
	int index;
	D3DRENDERSTATETYPE item;
	DWORD curStat;
	DWORD oldStat;
	bool enabled;
	DWORD newStat;

	rendStat(D3DRENDERSTATETYPE _item) :
		index(0),
		item(_item),
		curStat(0),
		oldStat(0),
		enabled(false),
		newStat(0) {
	}
};

std::string getRendStateType(D3DRENDERSTATETYPE State);
std::string getTransformStateType(D3DTRANSFORMSTATETYPE State);
std::string getSamplerStateType(D3DSAMPLERSTATETYPE State);
std::string getTextureStageStateType(D3DTEXTURESTAGESTATETYPE State);
std::string getFormatType(D3DFORMAT Format);
std::string getPoolType(D3DPOOL Pool);
std::string getUsageType(DWORD Usage);
std::string getPrimitiveType(D3DPRIMITIVETYPE PrimitiveType);
std::string getDeclType(BYTE Type);
std::string getDeclMethod(BYTE Method);
std::string getDeclUsage(BYTE Usage);

void SaveOriginalStates(IDirect3DDevice9* dxDev, bool runRendChanges);
std::vector<rendStat> GetChangedStates(IDirect3DDevice9* dxDev, bool runRendChanges);
void LoadOriginalStates(IDirect3DDevice9* dxDev);
void LoadNewStates(IDirect3DDevice9* dxDev);
void SetNewStates(int index, DWORD value);
#endif