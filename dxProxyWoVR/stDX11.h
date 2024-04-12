#pragma once
#include <dxgi1_2.h>
#include <d3d11.h>
#include <sstream>

struct stDX11
{
	UINT NumFeatureLevels;
	D3D_FEATURE_LEVEL FeatureLevels[5];
	D3D_FEATURE_LEVEL FeatureLevel;

	ID3D11Device* dev;
	ID3D11DeviceContext* devcon;
	IDXGISwapChain1* swapchain;
	ID3D11RenderTargetView* backbuffer;

	IDXGIFactory* factory;
	DWORD occlusionCookie;

	std::stringstream logError;

	stDX11() {
		FeatureLevel = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;
		FeatureLevels[0] = D3D_FEATURE_LEVEL_11_1;
		FeatureLevels[1] = D3D_FEATURE_LEVEL_11_0;
		FeatureLevels[2] = D3D_FEATURE_LEVEL_10_1;
		FeatureLevels[3] = D3D_FEATURE_LEVEL_10_0;
		FeatureLevels[4] = D3D_FEATURE_LEVEL_9_1;
		NumFeatureLevels = ARRAYSIZE(FeatureLevels);

		dev = nullptr;
		devcon = nullptr;
		swapchain = nullptr;
		factory = nullptr;
		backbuffer = nullptr;
		occlusionCookie = 0;
		logError.str("");
	}

	~stDX11() {
		Release();
	}

	bool createDevice() {
		UINT creationFlags = 0;// D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(_DEBUG)
		// If the project is in a debug build, enable the debug layer.
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		//logError << "(sDX11) Start CreateDXGIFactory1" << std::endl;
		HRESULT result = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&factory);
		if (FAILED(result)) {
			logError << "(sDX11) Failed to create DXGIFactory1. :" << std::hex << result << std::endl;
			return false;
		}
		//logError << "(sDX11) Finish CreateDXGIFactory1" << std::endl;

		//logError << "(sDX11) Start D3D11CreateDevice" << std::endl;
		result = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, NULL, NULL, NULL, D3D11_SDK_VERSION, NULL, &FeatureLevel, NULL);
		if (FAILED(result)) {
			logError << "(sDX11) Failed to return D3D11 FeatureLevel. :" << std::hex << result << std::endl;
			return false;
		}
		//logError << "(sDX11) D3D11 FeatureLevel 0x" << std::hex << FeatureLevel << std::endl;

		result = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, creationFlags, FeatureLevels, NumFeatureLevels, D3D11_SDK_VERSION, &dev, NULL, &devcon);
		if (FAILED(result)) {
			logError << "(sDX11) Failed to create D3D11 device. :" << std::hex << result << std::endl;
			return false;
		}
		//logError << "(sDX11) Finish D3D11CreateDevice" << std::endl;

		return true;
	}

	bool createFactory(HWND hWnd, bool disableAltEnter = false) {
#define OCCLUSION_STATUS_MSG WM_USER
		HRESULT result = S_OK;

		if (factory) { factory->Release(); factory = nullptr; }

		// Get DXGI device
		IDXGIDevice* DxgiDevice = nullptr;
		result = dev->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&DxgiDevice));
		if (FAILED(result)) {
			logError << "(sDX11) Failed to QI for DXGI device." << std::endl;
			return false;
		}

		// Get DXGI adapter
		IDXGIAdapter* DxgiAdapter = nullptr;
		result = DxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&DxgiAdapter));
		DxgiDevice->Release();
		DxgiDevice = nullptr;
		if (FAILED(result)) {
			logError << "(sDX11) Failed to get parent DXGI adapter." << std::endl;
			return false;
		}

		// Creates the factory
		result = DxgiAdapter->GetParent(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&factory));
		DxgiAdapter->Release();
		DxgiAdapter = nullptr;
		if (FAILED(result)) {
			logError << "(sDX11) Failed to get parent DXGI factory." << std::endl;
			return false;
		}

		if (hWnd != NULL) {
			// Register for occlusion status windows message
			//result = factory->RegisterOcclusionStatusWindow(hWnd, OCCLUSION_STATUS_MSG, &occlusionCookie);
			//if (FAILED(result)) {
			//	logError << "(sDX11) Failed to register for occlusion message." << std::endl;
			//	return false;
			//}
		}

		if (disableAltEnter) {
			// Disable the ALT-ENTER shortcut for entering full-screen mode
			result = factory->MakeWindowAssociation(hWnd, DXGI_MWA_NO_ALT_ENTER);
			if (FAILED(result)) {
				logError << "(sDX11) Failed to disable Alt-Enter." << std::endl;;
				return false;
			}
		}
		return true;
	}

	bool createSwapchain(HWND hWnd, int width, int height, bool disableAltEnter = false) {
		HRESULT result = S_OK;

		//bool retVal = createFactory(hWnd, disableAltEnter);
		//if (!retVal) { return false; }

		DXGI_SWAP_CHAIN_DESC1 scd;
		ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC1));
		scd.BufferCount = 1;
		scd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.Width = width;
		scd.Height = height;
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.SampleDesc.Count = 4;
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC scfd;
		ZeroMemory(&scfd, sizeof(DXGI_SWAP_CHAIN_FULLSCREEN_DESC));
		scfd.Windowed = true;

		//result = factory->CreateSwapChainForHwnd(dev, hWnd, &scd, &scfd, nullptr, &swapchain);

		if (FAILED(result)) {
			logError << "(sDX11) Failed to create swapchain" << std::endl;
			return false;
		}

		return true;
	}

	bool createBackBuffer() {
		HRESULT result = S_OK;

		// get the address of the back buffer
		ID3D11Texture2D* pBackBuffer;
		result = swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		if (FAILED(result)) {
			logError << "(sDX11) Failed to get backbuffer for render target." << std::endl;
			return false;
		}

		// use the back buffer address to create the render target
		result = dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
		pBackBuffer->Release();
		if (FAILED(result)) {
			logError << "(sDX11) Failed to create backbuffer target." << std::endl;
			return false;
		}
		return true;
	}

	DWORD isOccluded() {
		return occlusionCookie;
	}

	void Release() {
		if (backbuffer) { backbuffer->Release(); backbuffer = nullptr; }

		if (factory) { factory->Release(); factory = nullptr; }
		if (swapchain) { swapchain->Release(); swapchain = nullptr; }
		if (devcon) { devcon->Release(); devcon = nullptr; }
		if (dev) { dev->Release(); dev = nullptr; }
		return;
	}

	std::string GetErrors()
	{
		std::string curLog = logError.str();
		logError.str("");
		return curLog;
	}
};