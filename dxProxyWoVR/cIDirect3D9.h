#pragma once
#include "proxydll.h"

class cIDirect3D9 : public IDirect3D9Ex
{
public:
	cIDirect3D9(IDirect3D9Ex* pOriginal, bool showLog, std::stringstream *log);
	virtual ~cIDirect3D9();

	/*** IUnknown methods ***/
	HRESULT __stdcall QueryInterface(REFIID riid, LPVOID* ppv);
	ULONG   __stdcall AddRef();
	ULONG   __stdcall Release();

	/*** IDirect3D9 methods ***/
	HRESULT  __stdcall RegisterSoftwareDevice(void* pInitializeFunction);
	UINT     __stdcall GetAdapterCount();
	HRESULT	 __stdcall GetAdapterIdentifier(UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9* pIdentifier);
	UINT     __stdcall GetAdapterModeCount(UINT Adapter, D3DFORMAT Format);
	HRESULT  __stdcall EnumAdapterModes(UINT Adapter, D3DFORMAT Format, UINT Mode, D3DDISPLAYMODE* pMode);
	HRESULT	 __stdcall GetAdapterDisplayMode(UINT Adapter, D3DDISPLAYMODE* pMode);
	HRESULT	 __stdcall CheckDeviceType(UINT Adapter, D3DDEVTYPE DevType, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, BOOL bWindowed);
	HRESULT	 __stdcall CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat);
	HRESULT	 __stdcall CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, DWORD* pQualityLevels);
	HRESULT	 __stdcall CheckDepthStencilMatch(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat);
	HRESULT	 __stdcall CheckDeviceFormatConversion(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat);
	HRESULT	 __stdcall GetDeviceCaps(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9* pCaps);
	HMONITOR __stdcall GetAdapterMonitor(UINT Adapter);
	HRESULT	 __stdcall CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice9** ppReturnedDeviceInterface);
	UINT     __stdcall GetAdapterModeCountEx(UINT Adapter, CONST D3DDISPLAYMODEFILTER* pFilter);
	HRESULT  __stdcall EnumAdapterModesEx(UINT Adapter, CONST D3DDISPLAYMODEFILTER* pFilter, UINT Mode, D3DDISPLAYMODEEX* pMode);
	HRESULT  __stdcall GetAdapterDisplayModeEx(UINT Adapter, D3DDISPLAYMODEEX* pMode, D3DDISPLAYROTATION* pRotation);
	HRESULT  __stdcall CreateDeviceEx(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, D3DDISPLAYMODEEX* pFullscreenDisplayMode, IDirect3DDevice9Ex** ppReturnedDeviceInterface);
	HRESULT  __stdcall GetAdapterLUID(UINT Adapter, LUID* pLUID);

private:
	std::stringstream* logError;
	bool doLog = true;
	IDirect3D9Ex* m_pIDirect3D9;
};

