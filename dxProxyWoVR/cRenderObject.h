#pragma once
#pragma once
#include <D3D9.h>
#include <DirectXMath.h>
#include <iostream>
#include <vector>
#include <sstream>

using namespace DirectX;


struct intersectPoint
{
	float distance;
	XMVECTOR point;

	intersectPoint(float distance, XMVECTOR point)
	{
		this->distance = distance;
		this->point = point;
	}
};

class RenderObject
{
	IDirect3DDevice9* dev;
public:
	IDirect3DVertexDeclaration9* structLayout = nullptr;
	IDirect3DVertexShader9* vertexShader = nullptr;
	IDirect3DPixelShader9* pixelShader = nullptr;

	IDirect3DVertexBuffer9* vertexBuffer = nullptr;
	IDirect3DIndexBuffer9* indexBuffer = nullptr;

	std::vector<float> vertexList = std::vector<float>();
	std::vector<short> indexList = std::vector<short>();

	XMMATRIX objMatrix = XMMatrixIdentity();
	unsigned int stride = 0;
	unsigned int byteStride = 0;
	int vertexCount = 0;
	int indexCount = 0;

	bool vertexSet = false;
	bool indexSet = false;

public:
	RenderObject();
	RenderObject(IDirect3DDevice9* tdev);

	bool SetVertexBuffer(std::vector<float> vertices, int itmStride, bool ignoreCreateBuffer = false, D3DPOOL usage = D3DPOOL_DEFAULT);
	int GetVertexCount();
	bool SetIndexBuffer(std::vector<short> indices, bool ignoreCreateBuffer = false, D3DPOOL usage = D3DPOOL_DEFAULT);
	void SetShadersLayout(IDirect3DVertexDeclaration9* layout, IDirect3DVertexShader9* vertex, IDirect3DPixelShader9* pixel);
	void MapResourceVertex(void* data, int size);
	void MapResourceIndex(void* data, int size);

	void SetObjectMatrix(DirectX::XMMATRIX matrix);
	XMMATRIX GetObjectMatrix(bool inverse = false, bool transpose = false);

	bool RayIntersection(XMVECTOR origin, XMVECTOR direction, std::vector<intersectPoint>* intersection, std::vector<bool> interactable, std::stringstream* logError);
	bool RayTest(XMVECTOR origin, XMVECTOR direction, XMVECTOR v0, XMVECTOR v1, XMVECTOR v2, float* barycentricU, float* barycentricV, float* barycentricW, float* distance, std::stringstream* logError);

	void Render(D3DPRIMITIVETYPE type = D3DPT_TRIANGLELIST, int start = 0, int count = 0);

	void Release();
};






class RenderCurvedUI : public RenderObject
{

public:
	RenderCurvedUI(IDirect3DDevice9* tdev);
};

class RenderOSK : public RenderObject
{

public:
	RenderOSK(IDirect3DDevice9* tdev);
};

class RenderSquare : public RenderObject
{

public:
	RenderSquare(IDirect3DDevice9* tdev);
};

class RenderMaskUI : public RenderObject
{

public:
	RenderMaskUI(IDirect3DDevice9* tdev);
};

class RenderCube : public RenderObject
{

public:
	RenderCube(IDirect3DDevice9* tdev);
};

class RenderRayLine : public RenderObject
{

public:
	RenderRayLine(IDirect3DDevice9* tdev);
};

class RenderXYZGizmo : public RenderObject
{

public:
	RenderXYZGizmo(IDirect3DDevice9* tdev);
};
