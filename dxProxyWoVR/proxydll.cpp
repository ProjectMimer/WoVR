#include "proxydll.h"
#include "game_extras.h"

cIDirect3DDevice9* glIDirect3DDevice9;
cIDirect3DDevice9Ex* glIDirect3DDevice9Ex;
cIDirect3D9* glIDirect3D9;
HINSTANCE glOriginalDll;
HINSTANCE glThisInstance;

std::ofstream ofOut;
std::stringstream logError;
bool doLog = false;

bool HasErrors()
{
	return ((logError.rdbuf()->in_avail() == 0) ? false : true);
}

std::string GetErrors()
{
	std::string curLog = logError.str();
	logError.str("");
	return curLog;
}

void PrintErrors()
{
	if (HasErrors())
		ofOut << GetErrors();
}

void LoadOriginalDll(void)
{
	//if (doLog) logError << "-- LoadOriginalDll Start" << std::endl;
	if (glOriginalDll) return;
	char buffer[MAX_PATH];
	GetSystemDirectory(buffer, MAX_PATH);
	strcat_s(buffer, MAX_PATH, "\\d3d9.dll");
	//if (doLog) logError << "-- -- " << buffer << std::endl;

	TCHAR moduleName[1024];
	GetModuleFileName(glThisInstance, moduleName, sizeof(moduleName) / sizeof(TCHAR));
	//if (doLog) logError << "-- -- " << moduleName << std::endl;

	if (!glOriginalDll) glOriginalDll = LoadLibrary(buffer);
	if (!glOriginalDll) {
		ExitProcess(0);
	}

	//if (doLog) logError << "-- LoadOriginalDll End" << std::endl;
	return;
}

void InitInstance(HANDLE hModule)
{
	ofOut.open("./vr/output.txt", std::ios::out);
	ofOut.precision(5);

	//if (doLog) logError << "InitInstance Start" << std::endl;

	glOriginalDll = NULL;
	glThisInstance = NULL;
	glIDirect3D9 = NULL;
	glIDirect3DDevice9 = NULL;
	glIDirect3DDevice9Ex = NULL;

	glThisInstance = (HINSTANCE)hModule;
	if (!glOriginalDll) LoadOriginalDll();
	//if (doLog) logError << "InitInstance Stop" << std::endl;
	PrintErrors();
	InitDetours(hModule);
	PrintErrors();
}

void ExitInstance()
{
	ExitDetours();
	//if (doLog) logError << "ExitInstance Start" << std::endl;
	if (glOriginalDll)
	{
		FreeLibrary(glOriginalDll);
		glOriginalDll = NULL;
	}
	//if (doLog) logError << "ExitInstance Stop" << std::endl;
	PrintErrors();
	ofOut.close();
	return;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: InitInstance(hModule); break;
	case DLL_PROCESS_DETACH: ExitInstance(); break;
	case DLL_THREAD_ATTACH:  break;
	case DLL_THREAD_DETACH:  break;
	}
	return TRUE;
}


int WINAPI D3DPERF_BeginEvent(D3DCOLOR col, LPCWSTR wszName)
{
	//if (doLog) logError << "D3DPERF_BeginEvent" << std::endl;
	//PrintErrors();
	typedef int (WINAPI* D3D9_Type)(D3DCOLOR col, LPCWSTR wszName);
	D3D9_Type D3D9_fn = (D3D9_Type)GetProcAddress(glOriginalDll, "D3DPERF_BeginEvent");
	return D3D9_fn(col, wszName);
}

int WINAPI D3DPERF_EndEvent(void)
{
	//if (doLog) logError << "D3DPERF_EndEvent" << std::endl;
	//PrintErrors();
	typedef int (WINAPI* D3D9_Type)();
	D3D9_Type D3D9_fn = (D3D9_Type)GetProcAddress(glOriginalDll, "D3DPERF_EndEvent");
	return D3D9_fn();
}

DWORD WINAPI D3DPERF_GetStatus(void)
{
	//if (doLog) logError << "D3DPERF_GetStatus" << std::endl;
	//PrintErrors();
	typedef DWORD(WINAPI* D3D9_Type)();
	D3D9_Type D3D9_fn = (D3D9_Type)GetProcAddress(glOriginalDll, "D3DPERF_GetStatus");
	return D3D9_fn();
}

BOOL WINAPI D3DPERF_QueryRepeatFrame(void)
{
	//if (doLog) logError << "D3DPERF_QueryRepeatFrame" << std::endl;
	//PrintErrors();
	typedef BOOL(WINAPI* D3D9_Type)();
	D3D9_Type D3D9_fn = (D3D9_Type)GetProcAddress(glOriginalDll, "D3DPERF_QueryRepeatFrame");
	return D3D9_fn();
}

void WINAPI D3DPERF_SetMarker(D3DCOLOR col, LPCWSTR wszName)
{
	//if (doLog) logError << "D3DPERF_SetMarkerp" << std::endl;
	//PrintErrors();
	typedef void (WINAPI* D3D9_Type)(D3DCOLOR col, LPCWSTR wszName);
	D3D9_Type D3D9_fn = (D3D9_Type)GetProcAddress(glOriginalDll, "D3DPERF_SetMarker");
	D3D9_fn(col, wszName);
}

void WINAPI D3DPERF_SetOptions(DWORD dwOptions)
{
	//if (doLog) logError << "D3DPERF_SetOptions" << std::endl;
	//PrintErrors();
	typedef void (WINAPI* D3D9_Type)(DWORD dwOptions);
	D3D9_Type D3D9_fn = (D3D9_Type)GetProcAddress(glOriginalDll, "D3DPERF_SetOptions");
	D3D9_fn(dwOptions);
}

void WINAPI D3DPERF_SetRegion(D3DCOLOR col, LPCWSTR wszName)
{
	//if (doLog) logError << "D3DPERF_SetRegion" << std::endl;
	//PrintErrors();
	typedef void (WINAPI* D3D9_Type)(D3DCOLOR col, LPCWSTR wszName);
	D3D9_Type D3D9_fn = (D3D9_Type)GetProcAddress(glOriginalDll, "D3DPERF_SetRegion");
	D3D9_fn(col, wszName);
}

IDirect3D9* WINAPI Direct3DCreate9(UINT SDKVersion)
{
	//if (doLog) logError << "Direct3DCreate9" << std::endl;
	//PrintErrors();
	typedef HRESULT(WINAPI* D3D9_Type)(UINT SDKVersion, IDirect3D9Ex**);
	D3D9_Type D3D9_fn = (D3D9_Type)GetProcAddress(glOriginalDll, "Direct3DCreate9Ex");

	if (!D3D9_fn) {
		ExitProcess(0);
	}

	IDirect3D9Ex* pIDirect3D9Ex_orig = nullptr;
	HRESULT result = D3D9_fn(SDKVersion, &pIDirect3D9Ex_orig);
	glIDirect3D9 = new cIDirect3D9(pIDirect3D9Ex_orig, doLog, &logError);
	PrintErrors();
	return glIDirect3D9;
}

HRESULT WINAPI Direct3DCreate9Ex(UINT SDKVersion, IDirect3D9Ex** pIDirect3D9Ex_orig)
{
	//if (doLog) logError << "Direct3DCreate9Ex" << std::endl;
	//PrintErrors();
	typedef HRESULT(WINAPI* D3D9_Type)(UINT SDKVersion, IDirect3D9Ex**);
	D3D9_Type D3D9_fn = (D3D9_Type)GetProcAddress(glOriginalDll, "Direct3DCreate9Ex");

	if (!D3D9_fn) {
		ExitProcess(0);
	}

	HRESULT result = D3D9_fn(SDKVersion, pIDirect3D9Ex_orig);
	glIDirect3D9 = new cIDirect3D9(*pIDirect3D9Ex_orig, doLog, &logError);
	*pIDirect3D9Ex_orig = glIDirect3D9;
	PrintErrors();
	return result;
}

void WINAPI Direct3DShaderValidatorCreate9()
{
	//if (doLog) logError << "Direct3DShaderValidatorCreate9" << std::endl;
	//PrintErrors();
	typedef void (WINAPI* D3D9_Type)();
	D3D9_Type D3D9_fn = (D3D9_Type)GetProcAddress(glOriginalDll, "Direct3DShaderValidatorCreate9");
	D3D9_fn();
}