#pragma once

union uMatrix
{
	float matrix[4][4];
	float _m[16];

	uMatrix* operator =(const float m[4][4])
	{
		memcpy_s(matrix, 4 * 4 * 4, m, 4 * 4 * 4);
		return this;
	}
};

struct Vector3
{
	float x;
	float y;
	float z;

	bool operator ==(const Vector3& a)
	{
		return (this->x == a.x && this->y == a.y && this->z == a.z) ? true : false;
	}

	Vector3 operator -(const Vector3& a)
	{
		return { this->x - a.x, this->y - a.y, this->z - a.z };
	}

	Vector3 operator +(const Vector3& a)
	{
		return { this->x + a.x, this->y + a.y, this->z + a.z };
	}

	Vector3 operator =(const float a[4])
	{
		return { a[0], a[1], a[2] };
	}
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
