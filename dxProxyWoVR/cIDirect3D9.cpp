#include "cIDirect3D9.h"

cIDirect3D9::cIDirect3D9(IDirect3D9Ex* pOriginal, bool showLogs, std::stringstream* log) : 
																				m_pIDirect3D9(pOriginal),
																				doLog(showLogs),
																				logError(log)
{
	//*logError << "cIDirect3D9 Construct" << std::endl;
}

cIDirect3D9::~cIDirect3D9()
{
	if (m_pIDirect3D9)
		m_pIDirect3D9->Release();
	//*logError << "cIDirect3D9 Destruct" << std::endl;
}

HRESULT __stdcall cIDirect3D9::QueryInterface(REFIID riid, LPVOID* ppv)
{
	return m_pIDirect3D9->QueryInterface(riid, ppv);
}

ULONG __stdcall cIDirect3D9::AddRef()
{
	return m_pIDirect3D9->AddRef();
}

ULONG __stdcall cIDirect3D9::Release()
{
	extern cIDirect3D9* glIDirect3D9;

	ULONG count = m_pIDirect3D9->Release();

	if (count == 0)
	{
		glIDirect3D9 = NULL;
		m_pIDirect3D9 = nullptr;
		delete this;
	}
	return count;
}

HRESULT __stdcall cIDirect3D9::RegisterSoftwareDevice(void* pInitializeFunction)
{
	return m_pIDirect3D9->RegisterSoftwareDevice(pInitializeFunction);
}

UINT __stdcall cIDirect3D9::GetAdapterCount()
{
	return m_pIDirect3D9->GetAdapterCount();
}

HRESULT __stdcall cIDirect3D9::GetAdapterIdentifier(UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9* pIdentifier)
{
	return m_pIDirect3D9->GetAdapterIdentifier(Adapter, Flags, pIdentifier);
}

UINT __stdcall cIDirect3D9::GetAdapterModeCount(UINT Adapter, D3DFORMAT Format)
{
	return m_pIDirect3D9->GetAdapterModeCount(Adapter, Format);
}

HRESULT __stdcall cIDirect3D9::EnumAdapterModes(UINT Adapter, D3DFORMAT Format, UINT Mode, D3DDISPLAYMODE* pMode)
{
	return m_pIDirect3D9->EnumAdapterModes(Adapter, Format, Mode, pMode);
}

HRESULT __stdcall cIDirect3D9::GetAdapterDisplayMode(UINT Adapter, D3DDISPLAYMODE* pMode)
{
	return m_pIDirect3D9->GetAdapterDisplayMode(Adapter, pMode);
}

HRESULT __stdcall cIDirect3D9::CheckDeviceType(UINT Adapter, D3DDEVTYPE DevType, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, BOOL bWindowed)
{
	return m_pIDirect3D9->CheckDeviceType(Adapter, DevType, AdapterFormat, BackBufferFormat, bWindowed);
}

HRESULT __stdcall cIDirect3D9::CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat)
{
	return m_pIDirect3D9->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);
}

HRESULT __stdcall cIDirect3D9::CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, DWORD* pQualityLevels)
{
	return m_pIDirect3D9->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType, pQualityLevels);
}

HRESULT __stdcall cIDirect3D9::CheckDepthStencilMatch(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat)
{
	return m_pIDirect3D9->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);
}

HRESULT __stdcall cIDirect3D9::CheckDeviceFormatConversion(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat)
{
	return m_pIDirect3D9->CheckDeviceFormatConversion(Adapter, DeviceType, SourceFormat, TargetFormat);
}

HRESULT __stdcall cIDirect3D9::GetDeviceCaps(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9* pCaps)
{
	return m_pIDirect3D9->GetDeviceCaps(Adapter, DeviceType, pCaps);
}

HMONITOR __stdcall cIDirect3D9::GetAdapterMonitor(UINT Adapter)
{
	return m_pIDirect3D9->GetAdapterMonitor(Adapter);
}

HRESULT __stdcall cIDirect3D9::CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice9** ppReturnedDeviceInterface)
{
	extern cIDirect3DDevice9* glIDirect3DDevice9;

	D3DDISPLAYMODEEX displayMode;
	displayMode.Size = sizeof(D3DDISPLAYMODEEX);
	displayMode.Format = pPresentationParameters->BackBufferFormat;
	displayMode.Width = pPresentationParameters->BackBufferWidth;
	displayMode.Height = pPresentationParameters->BackBufferHeight;
	displayMode.RefreshRate = pPresentationParameters->FullScreen_RefreshRateInHz;
	displayMode.ScanLineOrdering = D3DSCANLINEORDERING_PROGRESSIVE;

	/*if (doLog)
	{
		*logError << "Windowed: " << pPresentationParameters->Windowed << std::endl;
		*logError << "Format: " << displayMode.Format << std::endl;
		*logError << "Width: " << displayMode.Width << std::endl;
		*logError << "Height: " << displayMode.Height << std::endl;
		*logError << "RefreshRate: " << displayMode.RefreshRate << std::endl;
	}*/

	HRESULT hRet;
	IDirect3DDevice9* ppReturnedDeviceInterfaceRet = NULL;
	if (pPresentationParameters->Windowed) {
		hRet = m_pIDirect3D9->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, &ppReturnedDeviceInterfaceRet);
	}
	else {
		hRet = m_pIDirect3D9->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, &ppReturnedDeviceInterfaceRet);
	}

	if (SUCCEEDED(hRet))
	{
		//if (doLog) *logError << "CreateDevice Success" << std::endl;
		glIDirect3DDevice9 = new cIDirect3DDevice9(ppReturnedDeviceInterfaceRet, doLog, logError);
		if (glIDirect3DDevice9->isSet) {
			*ppReturnedDeviceInterface = glIDirect3DDevice9;
		}
		else {
			hRet = 0;
			*logError << "CreateDevice Failed" << std::endl;
		}
	}

	return hRet;
}

UINT __stdcall cIDirect3D9::GetAdapterModeCountEx(UINT Adapter, CONST D3DDISPLAYMODEFILTER* pFilter)
{
	return m_pIDirect3D9->GetAdapterModeCountEx(Adapter, pFilter);
}

HRESULT __stdcall cIDirect3D9::EnumAdapterModesEx(UINT Adapter, CONST D3DDISPLAYMODEFILTER* pFilter, UINT Mode, D3DDISPLAYMODEEX* pMode)
{
	return m_pIDirect3D9->EnumAdapterModesEx(Adapter, pFilter, Mode, pMode);
}

HRESULT __stdcall cIDirect3D9::GetAdapterDisplayModeEx(UINT Adapter, D3DDISPLAYMODEEX* pMode, D3DDISPLAYROTATION* pRotation)
{
	return m_pIDirect3D9->GetAdapterDisplayModeEx(Adapter, pMode, pRotation);
}

HRESULT __stdcall cIDirect3D9::CreateDeviceEx(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, D3DDISPLAYMODEEX* pFullscreenDisplayMode, IDirect3DDevice9Ex** ppReturnedDeviceInterface)
{
	extern cIDirect3DDevice9Ex* glIDirect3DDevice9Ex;

	IDirect3DDevice9Ex* ppReturnedDeviceInterfaceRetEx = NULL;
	HRESULT hRet = m_pIDirect3D9->CreateDeviceEx(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, pFullscreenDisplayMode, &ppReturnedDeviceInterfaceRetEx);
	if (SUCCEEDED(hRet))
	{
		//if (doLog) *logError << "CreateDeviceEx Success" << std::endl;
		glIDirect3DDevice9Ex = new cIDirect3DDevice9Ex(ppReturnedDeviceInterfaceRetEx, doLog, logError);
		if (glIDirect3DDevice9Ex->isSet) {
			*ppReturnedDeviceInterface = glIDirect3DDevice9Ex;
		}
		else {
			hRet = 0;
			*logError << "CreateDeviceEx Failed" << std::endl;
		}
	}
	return hRet;
}

HRESULT __stdcall cIDirect3D9::GetAdapterLUID(UINT Adapter, LUID* pLUID)
{
	return m_pIDirect3D9->GetAdapterLUID(Adapter, pLUID);
}
