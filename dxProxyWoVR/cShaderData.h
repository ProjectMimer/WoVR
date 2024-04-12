#pragma once
#include <D3D9.h>
#include <D3DCompiler.h>
#include <sstream>
#include <vector>

class ShaderData
{
	std::string sName = "";
	std::string sVersion = "";
	std::string sSource = "";
	std::vector<D3DVERTEXELEMENT9> rawLayout = std::vector<D3DVERTEXELEMENT9>();

public:
	IDirect3DVertexShader9* VS = nullptr;
	IDirect3DPixelShader9* PS = nullptr;
	IDirect3DVertexDeclaration9* Layout = nullptr;

	void SetSource(std::string, std::string, std::string);
	void ClearLayout();
	void AddLayout(D3DVERTEXELEMENT9);
	bool CompileShaderFromString(IDirect3DDevice9* dev);
	void Release();
};


class VertexShaderTexture : public ShaderData
{
public:
	VertexShaderTexture();
};
class VertexShaderColor : public ShaderData
{
public:
	VertexShaderColor();
};
class PixelShaderColor : public ShaderData
{
public:
	PixelShaderColor();
};
class PixelShaderMask : public ShaderData
{
public:
	PixelShaderMask();
};
class PixelShaderWithMouseDot : public ShaderData
{
public:
	PixelShaderWithMouseDot();
};
class PixelShaderTexture : public ShaderData
{
public:
	PixelShaderTexture();
};
