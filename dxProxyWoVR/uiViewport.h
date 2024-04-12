#pragma once
#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d9.h>

extern std::stringstream logError;

using namespace DirectX;

struct uiViewport
{
	RECT position;
	float uv[4];
	Vector3 offset;
	Vector3 rotation;
	Vector3 scale;
	XMMATRIX matPosition;
	int bufferStart;
	bool enableDetect;
	bool show;

	#define M_PI		3.14159265358979323846f
	float Deg2Rad = M_PI / 180.0f;
	float Rad2Deg = 180.0f / M_PI;

	uiViewport()
	{
		setPosition(0, 0, 0, 0);
		setUV(0, 0, 0, 0);
		setOffset(0,0, 0);
		setRotation(0, 0, 0);
		setScale(0, 0, 0);
		calculateMatrix();
		bufferStart = 0;
		enableDetect = false;
		show = false;
	}

	uiViewport(IDirect3DDevice9* d3dDevice, int left, int top, int width, int height, float ox, float oy, float oz, float rx, float ry, float rz, float sx, float sy, float sz, bool enableDetection) {
		setPosition(left, top, width, height);
		setUV(0, 0, 0, 0);
		setOffset(ox, oy, oz);
		setRotation(rx, ry, rz);
		setScale(sx, sy, sz);
		calculateMatrix();
		bufferStart = 0;
		enableDetect = enableDetection;
		show = true;
	}

	uiViewport(IDirect3DDevice9* d3dDevice, RECT pos, float ox, float oy, float oz, float rx, float ry, float rz, float sx, float sy, float sz, bool enableDetection) {
		setPosition(pos.left, pos.top, pos.right, pos.bottom);
		setUV(0, 0, 0, 0);
		setOffset(ox, oy, oz);
		setRotation(rx, ry, rz);
		setScale(sx, sy, sz);
		calculateMatrix();
		bufferStart = 0;
		enableDetect = enableDetection;
		show = true;
	}

	uiViewport(IDirect3DDevice9* d3dDevice, float left, float top, float width, float height, float ox, float oy, float oz, float rx, float ry, float rz, float sx, float sy, float sz, bool enableDetection) {
		setPosition(0, 0, 1, 1);
		setUV(left, top, width, height);
		setOffset(ox, oy, oz);
		setRotation(rx, ry, rz);
		setScale(sx, sy, sz);
		calculateMatrix();
		bufferStart = 0;
		enableDetect = enableDetection;
		show = true;
	}

	void setPosition(int left, int top, int right, int bottom) {
		position.left = left;
		position.top = top;
		position.right = right;
		position.bottom = bottom;
	}

	void setUV(float left, float top, float right, float bottom) {
		uv[0] = left;
		uv[1] = top;
		uv[2] = right;
		uv[3] = bottom;
	}

	void setOffset(float x, float y, float z) {
		offset.x = x;
		offset.y = y;
		offset.z = z;
	}

	void setRotation(float x, float y, float z) {
		rotation.x = x;
		rotation.y = y;
		rotation.z = z;
	}

	void setScale(float x, float y, float z) {
		scale.x = x;
		scale.y = y;
		scale.z = z;
	}

	void calculateMatrix() {
		//----
		// Sets up the location / rotation of the viewports
		//----
		XMMATRIX rotateX = XMMatrixRotationX(rotation.x * Deg2Rad);
		XMMATRIX rotateY = XMMatrixRotationY(rotation.y * Deg2Rad);
		XMMATRIX rotateZ = XMMatrixRotationZ(rotation.z * Deg2Rad);

		XMMATRIX viewportRot = rotateX * rotateY * rotateZ;
		XMMATRIX viewportScale = XMMatrixScaling(scale.x, scale.y, scale.z);
		XMMATRIX viewportLoc = XMMatrixTranslation(offset.x, offset.y, offset.z);

		// changes the viewport scale location and rotation
		matPosition = (viewportScale * viewportLoc) * viewportRot;
	}

	void setBufferStart(int bufStart) {
		bufferStart = bufStart;
	}
};