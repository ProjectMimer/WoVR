#include "cShaderData.h"

void ShaderData::SetSource(std::string name, std::string version, std::string source)
{
	sName = name;
	sVersion = version;
	sSource = source;
}

void ShaderData::ClearLayout()
{
	rawLayout.clear();
}

void ShaderData::AddLayout(D3DVERTEXELEMENT9 element)
{
	rawLayout.push_back(element);
}

bool ShaderData::CompileShaderFromString(IDirect3DDevice9* dev)
{
	HRESULT result = S_OK;
	ID3D10Blob* errorMessage;
	ID3D10Blob* shader;

	DWORD flags = D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR | D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_WARNINGS_ARE_ERRORS;
#ifdef _DEBUG
	flags |= D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_DEBUG;
#else
	flags |= D3DCOMPILE_OPTIMIZATION_LEVEL3;
#endif

	result = D3DCompile(sSource.c_str(), strlen(sSource.c_str()), 0, 0, 0, sName.c_str(), sVersion.c_str(), flags, 0, &shader, &errorMessage);
	if (FAILED(result)) {
		if (errorMessage) {
			std::string errorMsg = "Error compiling shader '" + sName + "'";
			MessageBoxA(0, errorMsg.c_str(), "CompileShaderFromString", MB_OK);
			return false;
		}
		else {
			std::string errorMsg = "Error compiling shader '" + sName + "'";
			MessageBoxA(0, errorMsg.c_str(), "CompileShaderFromString", MB_OK);
			return false;
		}
	}

	result = S_OK;
	if (sVersion.substr(0, 3) == "vs_")
	{
		result = dev->CreateVertexDeclaration(&rawLayout[0], &Layout);
		if (FAILED(result)) {
			std::string errorMsg = "Error creating layout for shader '" + sName + "'";
			MessageBoxA(0, errorMsg.c_str(), "CompileShaderFromString", MB_OK);
			return false;
		}

		result = dev->CreateVertexShader((DWORD*)shader->GetBufferPointer(), &VS);
	}
	else if (sVersion.substr(0, 3) == "ps_")
		result = dev->CreatePixelShader((DWORD*)shader->GetBufferPointer(), &PS);

	if (FAILED(result)) {
		std::string errorMsg = "Error creating shader '" + sName + "'";
		MessageBoxA(0, errorMsg.c_str(), "CompileShaderFromString", MB_OK);
		return false;
	}

	shader->Release();
	shader = nullptr;

	return true;
}

void ShaderData::Release()
{
	if (VS) { VS->Release(); VS = nullptr; }
	if (PS) { PS->Release(); PS = nullptr; }
	if (Layout) { Layout->Release(); Layout = nullptr; }
}