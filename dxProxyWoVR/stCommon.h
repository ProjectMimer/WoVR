#pragma once

union uMatrix
{
	float matrix[4][4];
	float _m[16];
};

struct Vector3
{
	float x;
	float y;
	float z;
};

enum poseType
{
	None = 0,
	Projection = 1,
	EyeOffset = 5,
	hmdPosition = 10,
	LeftHand = 20,
	LeftHandPalm = 21,
	RightHand = 30,
	RightHandPalm = 31,
};

struct stScreenLayout
{
	UINT64 pid = 0;
	HWND hwnd = 0;
	int width = 0;
	int height = 0;
	bool haveLayout = false;

	void SetFromSwapchain(IDXGISwapChain4* swapchain)
	{
		DXGI_SWAP_CHAIN_DESC swapDesc;
		swapchain->GetDesc(&swapDesc);
		hwnd = swapDesc.OutputWindow;
		width = swapDesc.BufferDesc.Width;
		height = swapDesc.BufferDesc.Height;
		haveLayout = true;
	}
};
