#pragma once
#include <d3d11_4.h>
#include <d3d9.h>
#include <sstream>
#include <map>
#include <wincodec.h>
#include <strsafe.h>


#if (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/) && !defined(DXGI_1_2_FORMATS)
#define DXGI_1_2_FORMATS
#endif

inline bool operator<  (const GUID& left, const GUID& Right) { return memcmp(&left, &Right, sizeof(Right)) < 0; }
inline bool operator<= (const GUID& left, const GUID& Right) { return memcmp(&left, &Right, sizeof(Right)) <= 0; }
inline bool operator>  (const GUID& left, const GUID& Right) { return memcmp(&left, &Right, sizeof(Right)) > 0; }
inline bool operator>= (const GUID& left, const GUID& Right) { return memcmp(&left, &Right, sizeof(Right)) >= 0; }
//inline bool operator== (const GUID& left, const GUID& Right) { return memcmp(&left, &Right, sizeof(Right)) == 0; }

class WIC_DXGI
{
	std::map<GUID, DXGI_FORMAT> DXGIFormat =
	{
		{ GUID_WICPixelFormatDontCare,				DXGI_FORMAT_UNKNOWN },
		{ GUID_WICPixelFormat128bppRGBAFloat,       DXGI_FORMAT_R32G32B32A32_FLOAT },
		{ GUID_WICPixelFormat64bppRGBAHalf,         DXGI_FORMAT_R16G16B16A16_FLOAT },
		{ GUID_WICPixelFormat64bppRGBA,             DXGI_FORMAT_R16G16B16A16_UNORM },
		{ GUID_WICPixelFormat32bppRGBA,             DXGI_FORMAT_R8G8B8A8_UNORM },
		{ GUID_WICPixelFormat32bppBGRA,             DXGI_FORMAT_B8G8R8A8_UNORM }, // DXGI 1.1
		{ GUID_WICPixelFormat32bppBGR,              DXGI_FORMAT_B8G8R8X8_UNORM }, // DXGI 1.1
		{ GUID_WICPixelFormat32bppRGBA1010102XR,    DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM }, // DXGI 1.1
		{ GUID_WICPixelFormat32bppRGBA1010102,      DXGI_FORMAT_R10G10B10A2_UNORM },
		{ GUID_WICPixelFormat32bppRGBE,             DXGI_FORMAT_R9G9B9E5_SHAREDEXP },
#ifdef DXGI_1_2_FORMATS
		{ GUID_WICPixelFormat16bppBGRA5551,         DXGI_FORMAT_B5G5R5A1_UNORM },
		{ GUID_WICPixelFormat16bppBGR565,           DXGI_FORMAT_B5G6R5_UNORM },
#endif // DXGI_1_2_FORMATS
		{ GUID_WICPixelFormat32bppGrayFloat,        DXGI_FORMAT_R32_FLOAT },
		{ GUID_WICPixelFormat16bppGrayHalf,         DXGI_FORMAT_R16_FLOAT },
		{ GUID_WICPixelFormat16bppGray,             DXGI_FORMAT_R16_UNORM },
		{ GUID_WICPixelFormat8bppGray,              DXGI_FORMAT_R8_UNORM },
		{ GUID_WICPixelFormat8bppAlpha,             DXGI_FORMAT_A8_UNORM },
#if (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/)
		{ GUID_WICPixelFormat96bppRGBFloat,         DXGI_FORMAT_R32G32B32_FLOAT },
#endif
	};

	std::map<DXGI_FORMAT, int> DXGIBitsPerPixel =
	{
		{ DXGI_FORMAT_UNKNOWN, 0 },
		{ DXGI_FORMAT_R32G32B32A32_FLOAT, 128 },
		{ DXGI_FORMAT_R16G16B16A16_FLOAT, 64 },
		{ DXGI_FORMAT_R16G16B16A16_UNORM, 64 },
		{ DXGI_FORMAT_R8G8B8A8_UNORM, 32 },
		{ DXGI_FORMAT_B8G8R8A8_UNORM, 32 },
		{ DXGI_FORMAT_B8G8R8X8_UNORM, 32 },
		{ DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM, 32 },
		{ DXGI_FORMAT_R10G10B10A2_UNORM, 32 },
		{ DXGI_FORMAT_R9G9B9E5_SHAREDEXP, 32 },
		{ DXGI_FORMAT_B5G5R5A1_UNORM, 16 },
		{ DXGI_FORMAT_B5G6R5_UNORM, 16 },
		{ DXGI_FORMAT_R32_FLOAT, 32 },
		{ DXGI_FORMAT_R16_FLOAT, 16 },
		{ DXGI_FORMAT_R16_UNORM, 16 },
		{ DXGI_FORMAT_R8_UNORM, 8 },
		{ DXGI_FORMAT_A8_UNORM, 8 },
		{ DXGI_FORMAT_R32G32B32_FLOAT, 96 }
	};

	std::map<WICPixelFormatGUID, WICPixelFormatGUID> WICBaseFormat =
	{
		{ GUID_WICPixelFormatBlackWhite,			GUID_WICPixelFormat8bppGray }, // DXGI_FORMAT_R8_UNORM
		{ GUID_WICPixelFormat1bppIndexed,           GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
		{ GUID_WICPixelFormat2bppIndexed,           GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
		{ GUID_WICPixelFormat4bppIndexed,           GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
		{ GUID_WICPixelFormat8bppIndexed,           GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
		{ GUID_WICPixelFormat2bppGray,              GUID_WICPixelFormat8bppGray }, // DXGI_FORMAT_R8_UNORM 
		{ GUID_WICPixelFormat4bppGray,              GUID_WICPixelFormat8bppGray }, // DXGI_FORMAT_R8_UNORM 
		{ GUID_WICPixelFormat16bppGrayFixedPoint,   GUID_WICPixelFormat16bppGrayHalf }, // DXGI_FORMAT_R16_FLOAT 
		{ GUID_WICPixelFormat32bppGrayFixedPoint,   GUID_WICPixelFormat32bppGrayFloat }, // DXGI_FORMAT_R32_FLOAT
		{ GUID_WICPixelFormat32bppGrayFixedPoint,   GUID_WICPixelFormat32bppGrayFloat }, // DXGI_FORMAT_R32_FLOAT
#ifdef DXGI_1_2_FORMATS
		{ GUID_WICPixelFormat16bppBGR555,           GUID_WICPixelFormat16bppBGRA5551 }, // DXGI_FORMAT_B5G5R5A1_UNORM
#else
		{ GUID_WICPixelFormat16bppBGR555,           GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM
		{ GUID_WICPixelFormat16bppBGRA5551,         GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM
		{ GUID_WICPixelFormat16bppBGR565,           GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM
#endif // DXGI_1_2_FORMATS
		{ GUID_WICPixelFormat32bppBGR101010,        GUID_WICPixelFormat32bppRGBA1010102 }, // DXGI_FORMAT_R10G10B10A2_UNORM
		{ GUID_WICPixelFormat24bppBGR,              GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
		{ GUID_WICPixelFormat24bppRGB,              GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
		{ GUID_WICPixelFormat32bppPBGRA,            GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
		{ GUID_WICPixelFormat32bppPRGBA,            GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
		{ GUID_WICPixelFormat48bppRGB,              GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
		{ GUID_WICPixelFormat48bppBGR,              GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
		{ GUID_WICPixelFormat64bppBGRA,             GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
		{ GUID_WICPixelFormat64bppPRGBA,            GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
		{ GUID_WICPixelFormat64bppPBGRA,            GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
		{ GUID_WICPixelFormat48bppRGBFixedPoint,    GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
		{ GUID_WICPixelFormat48bppBGRFixedPoint,    GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
		{ GUID_WICPixelFormat64bppRGBAFixedPoint,   GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
		{ GUID_WICPixelFormat64bppBGRAFixedPoint,   GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
		{ GUID_WICPixelFormat64bppRGBFixedPoint,    GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
		{ GUID_WICPixelFormat64bppRGBHalf,          GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
		{ GUID_WICPixelFormat48bppRGBHalf,          GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
		{ GUID_WICPixelFormat96bppRGBFixedPoint,    GUID_WICPixelFormat128bppRGBAFloat }, // DXGI_FORMAT_R32G32B32A32_FLOAT 
		{ GUID_WICPixelFormat128bppPRGBAFloat,      GUID_WICPixelFormat128bppRGBAFloat }, // DXGI_FORMAT_R32G32B32A32_FLOAT 
		{ GUID_WICPixelFormat128bppRGBFloat,        GUID_WICPixelFormat128bppRGBAFloat }, // DXGI_FORMAT_R32G32B32A32_FLOAT 
		{ GUID_WICPixelFormat128bppRGBAFixedPoint,  GUID_WICPixelFormat128bppRGBAFloat }, // DXGI_FORMAT_R32G32B32A32_FLOAT 
		{ GUID_WICPixelFormat128bppRGBFixedPoint,   GUID_WICPixelFormat128bppRGBAFloat }, // DXGI_FORMAT_R32G32B32A32_FLOAT 
		{ GUID_WICPixelFormat32bppCMYK,             GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM 
		{ GUID_WICPixelFormat64bppCMYK,             GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
		{ GUID_WICPixelFormat40bppCMYKAlpha,        GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
		{ GUID_WICPixelFormat80bppCMYKAlpha,        GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
#if (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/)
		{ GUID_WICPixelFormat32bppRGB,              GUID_WICPixelFormat32bppRGBA }, // DXGI_FORMAT_R8G8B8A8_UNORM
		{ GUID_WICPixelFormat64bppRGB,              GUID_WICPixelFormat64bppRGBA }, // DXGI_FORMAT_R16G16B16A16_UNORM
		{ GUID_WICPixelFormat64bppPRGBAHalf,        GUID_WICPixelFormat64bppRGBAHalf }, // DXGI_FORMAT_R16G16B16A16_FLOAT 
#endif
	};

	IWICImagingFactory* wicFactory = nullptr;

public:
	DXGI_FORMAT GetFormat(WICPixelFormatGUID wicFormat)
	{
		std::map<WICPixelFormatGUID, DXGI_FORMAT>::iterator it = DXGIFormat.find(wicFormat);
		if (it != DXGIFormat.end())
			return it->second;
		else
			return DXGI_FORMAT_UNKNOWN;
	}

	int GetBitsPerPixel(DXGI_FORMAT dxgiFormat)
	{
		std::map<DXGI_FORMAT, int>::iterator it = DXGIBitsPerPixel.find(dxgiFormat);
		if (it != DXGIBitsPerPixel.end())
			return it->second;
		else
			return 0;
	}

	WICPixelFormatGUID GetBaseFormat(WICPixelFormatGUID wicFormat)
	{
		std::map<WICPixelFormatGUID, WICPixelFormatGUID>::iterator it = WICBaseFormat.find(wicFormat);
		if (it != WICBaseFormat.end())
			return it->second;
		else
			return GUID_WICPixelFormatDontCare;
	}

	int LoadImageDataFromFile(const char* filename, BYTE** imageData, DXGI_FORMAT* format, int* width, int* height, int* filesize, int* texturePitch)
	{
		HRESULT result = S_OK;
		IWICBitmapDecoder* wicDecoder = NULL;
		IWICBitmapFrameDecode* wicFrame = NULL;
		IWICFormatConverter* wicConverter = NULL;

		bool imageConverted = false;

		WCHAR folderPath[MAX_PATH] = { 0 };

		StringCchPrintfW(folderPath, MAX_PATH, L"%S", filename);

		if (wicFactory == NULL)
		{
			result = CoInitialize(NULL);
			result = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&wicFactory));
			if (FAILED(result))
				return 1;
		}

		result = wicFactory->CreateDecoderFromFilename(folderPath, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &wicDecoder);
		if (FAILED(result))
			return 2;

		result = wicDecoder->GetFrame(0, &wicFrame);
		if (FAILED(result))
			return 3;

		WICPixelFormatGUID pixelFormat;
		result = wicFrame->GetPixelFormat(&pixelFormat);
		if (FAILED(result))
			return 4;

		UINT textureWidth, textureHeight;
		result = wicFrame->GetSize(&textureWidth, &textureHeight);
		if (FAILED(result))
			return 5;

		//----
		// Check the current format against itself to see if it needs to be converted
		//----
		DXGI_FORMAT dxgiFormat = GetFormat(pixelFormat);
		if (dxgiFormat == DXGI_FORMAT_UNKNOWN)
		{
			WICPixelFormatGUID pixelFormatBase = GetBaseFormat(pixelFormat);
			if (pixelFormat != pixelFormatBase)
			{
				result = wicFactory->CreateFormatConverter(&wicConverter);
				if (FAILED(result))
					return 6;

				BOOL canConvert = FALSE;
				result = wicConverter->CanConvert(pixelFormat, pixelFormatBase, &canConvert);
				if (FAILED(result) || !canConvert)
					return 7;

				result = wicConverter->Initialize(wicFrame, pixelFormatBase, WICBitmapDitherTypeErrorDiffusion, 0, 0, WICBitmapPaletteTypeCustom);
				if (FAILED(result))
					return 8;

				imageConverted = true;
				dxgiFormat = GetFormat(pixelFormatBase);
			}
		}

		*format = dxgiFormat;
		*width = textureWidth;
		*height = textureHeight;

		int bitsPerPixel = GetBitsPerPixel(*format);
		(*texturePitch) = (textureWidth * bitsPerPixel) / 8;
		*filesize = (*texturePitch) * textureHeight;

		*imageData = (BYTE*)malloc(*filesize);
		if (imageConverted)
		{
			result = wicConverter->CopyPixels(0, (*texturePitch), *filesize, *imageData);
			if (FAILED(result))
				return 9;
		}
		else
		{
			result = wicFrame->CopyPixels(0, (*texturePitch), *filesize, *imageData);
			if (FAILED(result))
				return 10;
		}

		if (wicDecoder) { wicDecoder->Release(); wicDecoder = NULL; };
		if (wicFrame) { wicFrame->Release(); wicFrame = NULL; };
		if (wicConverter) { wicConverter->Release(); wicConverter = NULL; };
		return 0;
	}
};

struct stBasicTexture9
{
	IDirect3DTexture9* pTexture;
	IDirect3DSurface9* pRenderTarget;
	IDirect3DSurface9* pShaderResource;
	IDirect3DSurface9* pDepthStencilView;
	HANDLE pSharedHandle;
	int creationType;
	std::stringstream logError;

	D3DFORMAT renderFormat;

	int width;
	int height;

	stBasicTexture9()
	{
		pTexture = nullptr;
		pRenderTarget = nullptr;
		pShaderResource = nullptr;
		pSharedHandle = nullptr;
		pDepthStencilView = nullptr;
		creationType = 0;
		logError.str("");

		renderFormat = D3DFMT_A8R8G8B8;
		width = 0;
		height = 0;
	}

	void SetWidthHeight(int tWidth, int tHeight)
	{
		width = tWidth;
		height = tHeight;
	}

	bool Create(IDirect3DDevice9* dev, bool rtv, bool srv, bool dsv, bool shared)
	{
		bool retVal = true;
		if (pSharedHandle && shared)
			retVal = CreateShared(dev, rtv, srv, dsv);
		else
			retVal = CreateNew(dev, rtv, srv, dsv, shared);
		return retVal;
	}

	bool CreateNew(IDirect3DDevice9* dev, bool rtv, bool srv, bool dsv, bool shared)
	{
		bool retVal = true;
		if (rtv)
		{
			HRESULT result = dev->CreateRenderTarget(width, height, renderFormat, D3DMULTISAMPLE_NONE, 0, true, &pRenderTarget, NULL);
			if (FAILED(result))
			{
				logError << "Failed to create dx9 RenderTarget View " << std::hex << result << std::endl;
				retVal = false;
			}
		}
		else if (dsv)
		{
			//HRESULT result = dev->CreateTexture(width, height, 1, D3DUSAGE_DEPTHSTENCIL, renderFormat, D3DPOOL_DEFAULT, &pTexture, NULL);
			HRESULT result = dev->CreateDepthStencilSurface(width, height, renderFormat, D3DMULTISAMPLE_NONE, 0, false, &pDepthStencilView, NULL);
			if (FAILED(result))
			{
				logError << "Failed to create dx9 DepthStencil View " << std::hex << result << std::endl;
				retVal = false;
			}
		}
		else
		{
			HRESULT result = dev->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, renderFormat, D3DPOOL_DEFAULT, &pTexture, NULL);
			if (FAILED(result))
			{
				logError << "Failed to create dx9 Texture " << std::hex << result << std::endl;
				retVal = false;
			}
		}

		creationType = 1;
		//if (shared)
			//GetSharedHandle();
		if (retVal == true && srv == true)
			retVal = CreateShaderResourceView(dev);
		return retVal;
	}

	bool CreateFromFile(IDirect3DDevice9* dev, bool rtv, bool srv, bool shared, const char* file_path)
	{
		BYTE* imageData;
		DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;
		int texturePitch = 0;
		int filesize = 0;

		bool retVal = true;
		WIC_DXGI imgLoader = WIC_DXGI();
		int result = imgLoader.LoadImageDataFromFile(file_path, &imageData, &format, &width, &height, &filesize, &texturePitch);
		if (result != 0)
		{
			logError << "Failed to load dx9 texture from file " << std::hex << file_path << " : " << result << std::endl;
			retVal = false;
		}
		else
		{
			IDirect3DTexture9* ptTexture;
			HRESULT result = dev->CreateTexture(width, height, 1, 0, renderFormat, D3DPOOL_SYSTEMMEM, &ptTexture, NULL);
			if (FAILED(result))
			{
				logError << "Failed to create dx9 temp texture from file " << std::hex << result << std::endl;
				retVal = false;
			}
			else
			{
				result = dev->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, renderFormat, D3DPOOL_DEFAULT, &pTexture, NULL);
				if (FAILED(result))
				{
					logError << "Failed to create dx9 texture from file " << std::hex << result << std::endl;
					retVal = false;
				}
				else
				{
					D3DLOCKED_RECT lockRect;
					result = ptTexture->LockRect(0, &lockRect, NULL, 0);
					memcpy_s(lockRect.pBits, filesize, imageData, filesize);
					result = ptTexture->UnlockRect(0);

					result = dev->UpdateTexture(ptTexture, pTexture);
				}
				ptTexture->Release();
			}
		}
		free(imageData);
		return retVal;
	}

	bool CreateShared(IDirect3DDevice9* dev, bool rtv, bool srv, bool dsv)
	{
		bool retVal = true;

		if (rtv)
		{
			HRESULT result = dev->CreateRenderTarget(width, height, renderFormat, D3DMULTISAMPLE_NONE, 0, true, &pRenderTarget, &pSharedHandle);
			if (FAILED(result))
			{
				logError << "Failed to create dx9 RenderTarget View " << std::hex << result << std::endl;
				retVal = false;
			}
		}
		else if (dsv)
		{
			HRESULT result = dev->CreateDepthStencilSurface(width, height, renderFormat, D3DMULTISAMPLE_NONE, 0, false, &pDepthStencilView, &pSharedHandle);
			if (FAILED(result))
			{
				logError << "Failed to create dx9 DepthStencil View " << std::hex << result << std::endl;
				retVal = false;
			}
		}
		else
		{
			HRESULT result = dev->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, renderFormat, D3DPOOL_DEFAULT, &pTexture, &pSharedHandle);
			if (FAILED(result))
			{
				logError << "Failed to create dx9 Texture " << std::hex << result << std::endl;
				retVal = false;
			}
		}


		creationType = 2;
		if (retVal == true && srv == true)
			retVal = CreateShaderResourceView(dev);
		return retVal;
	}

	bool CreateShaderResourceView(IDirect3DDevice9* dev)
	{
		HRESULT result = pTexture->GetSurfaceLevel(0, &pShaderResource);
		if (FAILED(result))
		{
			logError << "Failed to create dx9 ShaderResource View " << std::hex << result << std::endl;
			return false;
		}
		return true;
	}
	
	void Release()
	{
		if (creationType == 2) { pTexture = nullptr; }
		if (pDepthStencilView) { pDepthStencilView->Release(); pDepthStencilView = nullptr; }
		if (pShaderResource) { pShaderResource->Release(); pShaderResource = nullptr; }
		if (pRenderTarget) { pRenderTarget->Release(); pRenderTarget = nullptr; }
		if (pTexture) { pTexture->Release();  pTexture = nullptr; }
		pSharedHandle = nullptr;
		creationType = 0;
	}

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
};

struct stBasicTexture
{
	ID3D11Texture2D* pTexture;
	ID3D11RenderTargetView* pRenderTarget;
	ID3D11ShaderResourceView* pShaderResource;
	ID3D11DepthStencilView* pDepthStencilView;
	HANDLE pSharedHandle;
	int creationType;
	std::stringstream logError;

	D3D11_TEXTURE2D_DESC textureDesc;

	stBasicTexture()
	{
		pTexture = nullptr;
		pRenderTarget = nullptr;
		pShaderResource = nullptr;
		pSharedHandle = nullptr;
		pDepthStencilView = nullptr;
		creationType = 0;
		logError.str("");

		//----
		// Creates a generic texture desc
		//----
		ZeroMemory(&textureDesc, sizeof(D3D11_TEXTURE2D_DESC));
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = D3D11_RESOURCE_MISC_SHARED;
	}

	void SetWidthHeight(int tWidth, int tHeight)
	{
		textureDesc.Width = tWidth;
		textureDesc.Height = tHeight;
	}

	bool Create(ID3D11Device* dev, bool rtv, bool srv, bool dsv, bool shared)
	{
		bool retVal = true;
		if (pSharedHandle && shared)
			retVal = CreateShared(dev, rtv, srv, dsv);
		else
			retVal = CreateNew(dev, rtv, srv, dsv, shared);
		return retVal;
	}

	bool CreateNew(ID3D11Device* dev, bool rtv, bool srv, bool dsv, bool shared, D3D11_SUBRESOURCE_DATA* data = NULL)
	{
		bool retVal = true;
		HRESULT result = dev->CreateTexture2D(&textureDesc, data, &pTexture);
		if (FAILED(result))
		{
			logError << "Failed to create new Texture2D " << std::hex << result << std::endl;
			retVal = false;
		}
		creationType = 1;
		if (shared)
			GetSharedHandle();
		if (retVal == true && rtv == true)
			retVal = CreateRenderTargetView(dev);
		if (retVal == true && srv == true)
			retVal = CreateShaderResourceView(dev);
		if (retVal == true && dsv == true)
			retVal = CreateDepthStencilView(dev);
		return retVal;
	}

	bool CreateShared(ID3D11Device* dev, bool rtv, bool srv, bool dsv)
	{
		bool retVal = true;
		HRESULT result = dev->OpenSharedResource(pSharedHandle, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pTexture));
		if (FAILED(result))
		{
			logError << "Failed to create shared Texture2D " << std::hex << result << std::endl;
			retVal = false;
		}
		creationType = 2;

		if (retVal == true && rtv == true)
			retVal = CreateRenderTargetView(dev);
		if (retVal == true && srv == true)
			retVal = CreateShaderResourceView(dev);
		if (retVal == true && dsv == true)
			retVal = CreateDepthStencilView(dev);
		return retVal;
	}

	bool GetSharedHandle()
	{
		if (pTexture)
		{
			IDXGIResource* renderResource(NULL);
			HRESULT result = pTexture->QueryInterface(__uuidof(IDXGIResource), (LPVOID*)&renderResource);
			if (FAILED(result))
			{
				logError << "Failed to get Shared Resource " << std::hex << result << std::endl;
				return false;
			}
			renderResource->GetSharedHandle(&pSharedHandle);
			renderResource->Release();
			renderResource = nullptr;
		}
		return false;
	}

	bool CreateRenderTargetView(ID3D11Device* dev, DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN)
	{
		//----
		// Creates a generic render target desc
		//----
		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
		ZeroMemory(&renderTargetViewDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
		renderTargetViewDesc.Format = (format == DXGI_FORMAT_UNKNOWN) ? textureDesc.Format : format;
		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDesc.Texture2D.MipSlice = 0;

		HRESULT result = dev->CreateRenderTargetView(pTexture, &renderTargetViewDesc, &pRenderTarget);
		if (FAILED(result))
		{
			logError << "Failed to create RenderTarget View " << std::hex << result << std::endl;
			return false;
		}
		return true;
	}

	bool CreateShaderResourceView(ID3D11Device* dev, DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN)
	{
		//----
		// Creates a generic shader resource desc
		//----
		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
		ZeroMemory(&shaderResourceViewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		shaderResourceViewDesc.Format = (format == DXGI_FORMAT_UNKNOWN) ? textureDesc.Format : format;
		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
		shaderResourceViewDesc.Texture2D.MipLevels = 1;

		HRESULT result = dev->CreateShaderResourceView(pTexture, &shaderResourceViewDesc, &pShaderResource);
		if (FAILED(result))
		{
			logError << "Failed to create ShaderResource View " << std::hex << result << std::endl;
			return false;
		}
		return true;
	}

	bool CreateDepthStencilView(ID3D11Device* dev, DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN)
	{
		//----
		// Creates a generic depth stencil view desc
		//----
		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		ZeroMemory(&depthStencilViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		depthStencilViewDesc.Format = (format == DXGI_FORMAT_UNKNOWN) ? textureDesc.Format : format;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Texture2D.MipSlice = 0;

		HRESULT result = dev->CreateDepthStencilView(pTexture, &depthStencilViewDesc, &pDepthStencilView);
		if (FAILED(result))
		{
			logError << "Failed to create DepthStencil View " << std::hex << result << std::endl;
			return false;
		}

		return true;
	}

	void Release()
	{
		if (creationType == 2) { pTexture = nullptr; }
		if (pDepthStencilView) { pDepthStencilView->Release();  pDepthStencilView = nullptr; }
		if (pShaderResource) { pShaderResource->Release(); pShaderResource = nullptr; }
		if (pRenderTarget) { pRenderTarget->Release(); pRenderTarget = nullptr; }
		if (pTexture) { pTexture->Release();  pTexture = nullptr; }
		pSharedHandle = nullptr;
		creationType = 0;
	}

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
};
