#pragma once
#define WIN32_LEAN_AND_MEAN
// Windows Header Files
#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include "stBasicTexture.h"
#include "stCommon.h"

class OSK
{
	stScreenLayout oskLayout = stScreenLayout();
	stBasicTexture oskSharedTexture = stBasicTexture();
	stBasicTexture9 oskSharedTexture9 = stBasicTexture9();
	RECT displayRect = { 0, 0, 0, 0 };
	PROCESSENTRY32W FindProcess(std::wstring toFind);
	bool is9 = false;

public:
	void ToggleOSK();
	void CreateOSKTexture9(IDirect3DDevice9* device, stBasicTexture9* oskTexture);
	void CopyOSKTexture9(IDirect3DDevice9* device, stBasicTexture9* oskTexture);
	bool LoadOSK9(IDirect3DDevice9* device, stBasicTexture9* oskTexture, RECT position);

	void CreateOSKTexture(ID3D11Device* device, stBasicTexture* oskTexture);
	void CopyOSKTexture(ID3D11Device* device, ID3D11DeviceContext* devCon, stBasicTexture* oskTexture);
	bool LoadOSK(ID3D11Device* device, stBasicTexture* oskTexture, RECT position);
	stScreenLayout* GetOSKLayout();
	void ShowHide(bool show);
	void UnloadOSK();
};
