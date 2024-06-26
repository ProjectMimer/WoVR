#include "cIDirect3DDevice9.h"
#include "dx9Debug.h"

cIDirect3DDevice9::cIDirect3DDevice9(IDirect3DDevice9* pOriginal, bool showLogs, std::stringstream* log) : 
																	m_pIDirect3DDevice9(pOriginal),
																	doLog(showLogs),
																	logError(log),
																	isSet(false),
																	m_nRefCount(1)
{
	isSet = true;
	//*logError << "cIDirect3DDevice9 Construct" << std::endl;
}

cIDirect3DDevice9::~cIDirect3DDevice9()
{
	isSet = false;
	if (m_pIDirect3DDevice9)
		m_pIDirect3DDevice9->Release();
	//*logError << "cIDirect3DDevice9 Destruct" << std::endl;
}

HRESULT cIDirect3DDevice9::QueryInterface(REFIID riid, LPVOID* ppv)
{
	return m_pIDirect3DDevice9->QueryInterface(riid, ppv);
}

ULONG cIDirect3DDevice9::AddRef()
{
	return ++m_nRefCount;
}

ULONG cIDirect3DDevice9::Release()
{
	if (--m_nRefCount == 0)
	{
		delete this;
		return 0;
	}

	return m_nRefCount;
}

HRESULT cIDirect3DDevice9::TestCooperativeLevel()
{
	return m_pIDirect3DDevice9->TestCooperativeLevel();
}

UINT cIDirect3DDevice9::GetAvailableTextureMem()
{
	return m_pIDirect3DDevice9->GetAvailableTextureMem();
}

HRESULT cIDirect3DDevice9::EvictManagedResources()
{
	return m_pIDirect3DDevice9->EvictManagedResources();
}

HRESULT cIDirect3DDevice9::GetDirect3D(IDirect3D9** ppD3D9)
{
	return m_pIDirect3DDevice9->GetDirect3D(ppD3D9);
}

HRESULT cIDirect3DDevice9::GetDeviceCaps(D3DCAPS9* pCaps)
{
	return m_pIDirect3DDevice9->GetDeviceCaps(pCaps);
}

HRESULT cIDirect3DDevice9::GetDisplayMode(UINT iSwapChain, D3DDISPLAYMODE* pMode)
{
	return m_pIDirect3DDevice9->GetDisplayMode(iSwapChain, pMode);
}

HRESULT cIDirect3DDevice9::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS* pParameters)
{
	return m_pIDirect3DDevice9->GetCreationParameters(pParameters);
}

HRESULT cIDirect3DDevice9::SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9* pCursorBitmap)
{
	return m_pIDirect3DDevice9->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap);
}

void cIDirect3DDevice9::SetCursorPosition(int X, int Y, DWORD Flags)
{
	return m_pIDirect3DDevice9->SetCursorPosition(X, Y, Flags);
}

BOOL cIDirect3DDevice9::ShowCursor(BOOL bShow)
{
	return m_pIDirect3DDevice9->ShowCursor(bShow);
}

HRESULT cIDirect3DDevice9::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain9** pSwapChain)
{
	return m_pIDirect3DDevice9->CreateAdditionalSwapChain(pPresentationParameters, pSwapChain);
}

HRESULT cIDirect3DDevice9::GetSwapChain(UINT iSwapChain, IDirect3DSwapChain9** pSwapChain)
{
	return m_pIDirect3DDevice9->GetSwapChain(iSwapChain, pSwapChain);
}

UINT cIDirect3DDevice9::GetNumberOfSwapChains()
{
	return m_pIDirect3DDevice9->GetNumberOfSwapChains();
}

HRESULT cIDirect3DDevice9::Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	return m_pIDirect3DDevice9->Reset(pPresentationParameters);
}

HRESULT cIDirect3DDevice9::Present(CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
	return m_pIDirect3DDevice9->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

HRESULT cIDirect3DDevice9::GetBackBuffer(UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9** ppBackBuffer)
{
	return m_pIDirect3DDevice9->GetBackBuffer(iSwapChain, iBackBuffer, Type, ppBackBuffer);
}

HRESULT cIDirect3DDevice9::GetRasterStatus(UINT iSwapChain, D3DRASTER_STATUS* pRasterStatus)
{
	return m_pIDirect3DDevice9->GetRasterStatus(iSwapChain, pRasterStatus);
}

HRESULT cIDirect3DDevice9::SetDialogBoxMode(BOOL bEnableDialogs)
{
	return m_pIDirect3DDevice9->SetDialogBoxMode(bEnableDialogs);
}

void cIDirect3DDevice9::SetGammaRamp(UINT iSwapChain, DWORD Flags, CONST D3DGAMMARAMP* pRamp)
{
	return m_pIDirect3DDevice9->SetGammaRamp(iSwapChain, Flags, pRamp);
}

void cIDirect3DDevice9::GetGammaRamp(UINT iSwapChain, D3DGAMMARAMP* pRamp)
{
	return m_pIDirect3DDevice9->GetGammaRamp(iSwapChain, pRamp);
}

HRESULT cIDirect3DDevice9::CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle)
{
	if (Usage == 0) { Usage = D3DUSAGE_DYNAMIC; }
	if (Pool == D3DPOOL_MANAGED) { Pool = D3DPOOL_DEFAULT; }
	return m_pIDirect3DDevice9->CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);

	/*HRESULT result = m_pIDirect3DDevice9->CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);
	if (Pool == D3DPOOL_DEFAULT && Levels == 1 && Format == 26)
	{
		std::ofstream ofOut("texture.txt", std::ios_base::app);
		ofOut << "CreateTexture - result: " << result << ", Width: " << Width << ", Height: " << Height << ", Levels: " << Levels << ", Usage: " << getUsageType(Usage) << ", Format: " << getFormatType(Format) << ", Pool: " << getPoolType(Pool) << ", ppTexture: " << *ppTexture << ", pSharedHandle: " << pSharedHandle << std::endl;
		ofOut.close();
	}
	return result;*/
}

HRESULT cIDirect3DDevice9::CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9** ppVolumeTexture, HANDLE* pSharedHandle)
{
	if (Usage == 0) { Usage = D3DUSAGE_DYNAMIC; }
	if (Pool == D3DPOOL_MANAGED) { Pool = D3DPOOL_DEFAULT; }
	return m_pIDirect3DDevice9->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);
}

HRESULT cIDirect3DDevice9::CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture, HANDLE* pSharedHandle)
{
	if (Usage == 0) { Usage = D3DUSAGE_DYNAMIC; }
	if (Pool == D3DPOOL_MANAGED) { Pool = D3DPOOL_DEFAULT; }
	return m_pIDirect3DDevice9->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle);
}

HRESULT cIDirect3DDevice9::CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle)
{
	if (Usage == 0) { Usage = D3DUSAGE_DYNAMIC; }
	if (Pool == D3DPOOL_MANAGED) { Pool = D3DPOOL_DEFAULT; }
	return m_pIDirect3DDevice9->CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);
}

HRESULT cIDirect3DDevice9::CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle)
{
	if (Usage == 0) { Usage = D3DUSAGE_DYNAMIC; }
	if (Pool == D3DPOOL_MANAGED) { Pool = D3DPOOL_DEFAULT; }
	return m_pIDirect3DDevice9->CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);
}

HRESULT cIDirect3DDevice9::CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	return m_pIDirect3DDevice9->CreateRenderTarget(Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle);
}

HRESULT cIDirect3DDevice9::CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	return m_pIDirect3DDevice9->CreateDepthStencilSurface(Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle);
}

HRESULT cIDirect3DDevice9::UpdateSurface(IDirect3DSurface9* pSourceSurface, CONST RECT* pSourceRect, IDirect3DSurface9* pDestinationSurface, CONST POINT* pDestPoint)
{
	return m_pIDirect3DDevice9->UpdateSurface(pSourceSurface, pSourceRect, pDestinationSurface, pDestPoint);
}

HRESULT cIDirect3DDevice9::UpdateTexture(IDirect3DBaseTexture9* pSourceTexture, IDirect3DBaseTexture9* pDestinationTexture)
{
	return m_pIDirect3DDevice9->UpdateTexture(pSourceTexture, pDestinationTexture);
}

HRESULT cIDirect3DDevice9::GetRenderTargetData(IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface)
{
	return m_pIDirect3DDevice9->GetRenderTargetData(pRenderTarget, pDestSurface);
}

HRESULT cIDirect3DDevice9::GetFrontBufferData(UINT iSwapChain, IDirect3DSurface9* pDestSurface)
{
	return m_pIDirect3DDevice9->GetFrontBufferData(iSwapChain, pDestSurface);
}

HRESULT cIDirect3DDevice9::StretchRect(IDirect3DSurface9* pSourceSurface, CONST RECT* pSourceRect, IDirect3DSurface9* pDestSurface, CONST RECT* pDestRect, D3DTEXTUREFILTERTYPE Filter)
{
	return m_pIDirect3DDevice9->StretchRect(pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter);
}

HRESULT cIDirect3DDevice9::ColorFill(IDirect3DSurface9* pSurface, CONST RECT* pRect, D3DCOLOR color)
{
	return m_pIDirect3DDevice9->ColorFill(pSurface, pRect, color);
}

HRESULT cIDirect3DDevice9::CreateOffscreenPlainSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	if (Pool == D3DPOOL_MANAGED) { Pool = D3DPOOL_DEFAULT; }
	return m_pIDirect3DDevice9->CreateOffscreenPlainSurface(Width, Height, Format, Pool, ppSurface, pSharedHandle);
}

HRESULT cIDirect3DDevice9::SetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9* pRenderTarget)
{
	return m_pIDirect3DDevice9->SetRenderTarget(RenderTargetIndex, pRenderTarget);
}

HRESULT cIDirect3DDevice9::GetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9** ppRenderTarget)
{
	return m_pIDirect3DDevice9->GetRenderTarget(RenderTargetIndex, ppRenderTarget);
}

HRESULT cIDirect3DDevice9::SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil)
{
	return m_pIDirect3DDevice9->SetDepthStencilSurface(pNewZStencil);
}

HRESULT cIDirect3DDevice9::GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface)
{
	return m_pIDirect3DDevice9->GetDepthStencilSurface(ppZStencilSurface);
}

HRESULT cIDirect3DDevice9::BeginScene()
{
	return m_pIDirect3DDevice9->BeginScene();
}

HRESULT cIDirect3DDevice9::EndScene()
{
	return m_pIDirect3DDevice9->EndScene();
}

HRESULT cIDirect3DDevice9::Clear(DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
{
	return m_pIDirect3DDevice9->Clear(Count, pRects, Flags, Color, Z, Stencil);
}

HRESULT cIDirect3DDevice9::SetTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix)
{
	return m_pIDirect3DDevice9->SetTransform(State, pMatrix);
}

HRESULT cIDirect3DDevice9::GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix)
{
	return m_pIDirect3DDevice9->GetTransform(State, pMatrix);
}

HRESULT cIDirect3DDevice9::MultiplyTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix)
{
	return m_pIDirect3DDevice9->MultiplyTransform(State, pMatrix);
}

HRESULT cIDirect3DDevice9::SetViewport(CONST D3DVIEWPORT9* pViewport)
{
	return m_pIDirect3DDevice9->SetViewport(pViewport);
}

HRESULT cIDirect3DDevice9::GetViewport(D3DVIEWPORT9* pViewport)
{
	return m_pIDirect3DDevice9->GetViewport(pViewport);
}

HRESULT cIDirect3DDevice9::SetMaterial(CONST D3DMATERIAL9* pMaterial)
{
	return m_pIDirect3DDevice9->SetMaterial(pMaterial);
}

HRESULT cIDirect3DDevice9::GetMaterial(D3DMATERIAL9* pMaterial)
{
	return m_pIDirect3DDevice9->GetMaterial(pMaterial);
}

HRESULT cIDirect3DDevice9::SetLight(DWORD Index, CONST D3DLIGHT9* pLight)
{
	return m_pIDirect3DDevice9->SetLight(Index, pLight);
}

HRESULT cIDirect3DDevice9::GetLight(DWORD Index, D3DLIGHT9* pLight)
{
	return m_pIDirect3DDevice9->GetLight(Index, pLight);
}

HRESULT cIDirect3DDevice9::LightEnable(DWORD Index, BOOL Enable)
{
	return m_pIDirect3DDevice9->LightEnable(Index, Enable);
}

HRESULT cIDirect3DDevice9::GetLightEnable(DWORD Index, BOOL* pEnable)
{
	return m_pIDirect3DDevice9->GetLightEnable(Index, pEnable);
}

HRESULT cIDirect3DDevice9::SetClipPlane(DWORD Index, CONST float* pPlane)
{
	return m_pIDirect3DDevice9->SetClipPlane(Index, pPlane);
}

HRESULT cIDirect3DDevice9::GetClipPlane(DWORD Index, float* pPlane)
{
	return m_pIDirect3DDevice9->GetClipPlane(Index, pPlane);
}

HRESULT cIDirect3DDevice9::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
	return m_pIDirect3DDevice9->SetRenderState(State, Value);
}

HRESULT cIDirect3DDevice9::GetRenderState(D3DRENDERSTATETYPE State, DWORD* pValue)
{
	return m_pIDirect3DDevice9->GetRenderState(State, pValue);
}

HRESULT cIDirect3DDevice9::CreateStateBlock(D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9** ppSB)
{
	return m_pIDirect3DDevice9->CreateStateBlock(Type, ppSB);
}

HRESULT cIDirect3DDevice9::BeginStateBlock()
{
	return m_pIDirect3DDevice9->BeginStateBlock();
}

HRESULT cIDirect3DDevice9::EndStateBlock(IDirect3DStateBlock9** ppSB)
{
	return m_pIDirect3DDevice9->EndStateBlock(ppSB);
}

HRESULT cIDirect3DDevice9::SetClipStatus(CONST D3DCLIPSTATUS9* pClipStatus)
{
	return m_pIDirect3DDevice9->SetClipStatus(pClipStatus);
}

HRESULT cIDirect3DDevice9::GetClipStatus(D3DCLIPSTATUS9* pClipStatus)
{
	return m_pIDirect3DDevice9->GetClipStatus(pClipStatus);
}

HRESULT cIDirect3DDevice9::GetTexture(DWORD Stage, IDirect3DBaseTexture9** ppTexture)
{
	return m_pIDirect3DDevice9->GetTexture(Stage, ppTexture);
}

HRESULT cIDirect3DDevice9::SetTexture(DWORD Stage, IDirect3DBaseTexture9* pTexture)
{
	return m_pIDirect3DDevice9->SetTexture(Stage, pTexture);
}

HRESULT cIDirect3DDevice9::GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue)
{
	return m_pIDirect3DDevice9->GetTextureStageState(Stage, Type, pValue);
}

HRESULT cIDirect3DDevice9::SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)
{
	return m_pIDirect3DDevice9->SetTextureStageState(Stage, Type, Value);
}

HRESULT cIDirect3DDevice9::GetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD* pValue)
{
	return m_pIDirect3DDevice9->GetSamplerState(Sampler, Type, pValue);
}

HRESULT cIDirect3DDevice9::SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value)
{
	return m_pIDirect3DDevice9->SetSamplerState(Sampler, Type, Value);
}

HRESULT cIDirect3DDevice9::ValidateDevice(DWORD* pNumPasses)
{
	return m_pIDirect3DDevice9->ValidateDevice(pNumPasses);
}

HRESULT cIDirect3DDevice9::SetPaletteEntries(UINT PaletteNumber, CONST PALETTEENTRY* pEntries)
{
	return m_pIDirect3DDevice9->SetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT cIDirect3DDevice9::GetPaletteEntries(UINT PaletteNumber, PALETTEENTRY* pEntries)
{
	return m_pIDirect3DDevice9->GetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT cIDirect3DDevice9::SetCurrentTexturePalette(UINT PaletteNumber)
{
	return m_pIDirect3DDevice9->SetCurrentTexturePalette(PaletteNumber);
}

HRESULT cIDirect3DDevice9::GetCurrentTexturePalette(UINT* PaletteNumber)
{
	return m_pIDirect3DDevice9->GetCurrentTexturePalette(PaletteNumber);
}

HRESULT cIDirect3DDevice9::SetScissorRect(CONST RECT* pRect)
{
	return m_pIDirect3DDevice9->SetScissorRect(pRect);
}

HRESULT cIDirect3DDevice9::GetScissorRect(RECT* pRect)
{
	return m_pIDirect3DDevice9->GetScissorRect(pRect);
}

HRESULT cIDirect3DDevice9::SetSoftwareVertexProcessing(BOOL bSoftware)
{
	return m_pIDirect3DDevice9->SetSoftwareVertexProcessing(bSoftware);
}

BOOL cIDirect3DDevice9::GetSoftwareVertexProcessing()
{
	return m_pIDirect3DDevice9->GetSoftwareVertexProcessing();
}

HRESULT cIDirect3DDevice9::SetNPatchMode(float nSegments)
{
	return m_pIDirect3DDevice9->SetNPatchMode(nSegments);
}

float cIDirect3DDevice9::GetNPatchMode()
{
	return m_pIDirect3DDevice9->GetNPatchMode();
}

HRESULT cIDirect3DDevice9::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
	return m_pIDirect3DDevice9->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}

HRESULT cIDirect3DDevice9::DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
	return m_pIDirect3DDevice9->DrawIndexedPrimitive(PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

HRESULT cIDirect3DDevice9::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return m_pIDirect3DDevice9->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT cIDirect3DDevice9::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, CONST void* pIndexData, D3DFORMAT IndexDataFormat, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return m_pIDirect3DDevice9->DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT cIDirect3DDevice9::ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9* pDestBuffer, IDirect3DVertexDeclaration9* pVertexDecl, DWORD Flags)
{
	return m_pIDirect3DDevice9->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags);
}

HRESULT cIDirect3DDevice9::CreateVertexDeclaration(CONST D3DVERTEXELEMENT9* pVertexElements, IDirect3DVertexDeclaration9** ppDecl)
{
	return m_pIDirect3DDevice9->CreateVertexDeclaration(pVertexElements, ppDecl);
}

HRESULT cIDirect3DDevice9::SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl)
{
	return m_pIDirect3DDevice9->SetVertexDeclaration(pDecl);
}

HRESULT cIDirect3DDevice9::GetVertexDeclaration(IDirect3DVertexDeclaration9** ppDecl)
{
	return m_pIDirect3DDevice9->GetVertexDeclaration(ppDecl);
}

HRESULT cIDirect3DDevice9::SetFVF(DWORD FVF)
{
	return m_pIDirect3DDevice9->SetFVF(FVF);
}

HRESULT cIDirect3DDevice9::GetFVF(DWORD* pFVF)
{
	return m_pIDirect3DDevice9->GetFVF(pFVF);
}

HRESULT cIDirect3DDevice9::CreateVertexShader(CONST DWORD* pFunction, IDirect3DVertexShader9** ppShader)
{
	return m_pIDirect3DDevice9->CreateVertexShader(pFunction, ppShader);
}

HRESULT cIDirect3DDevice9::SetVertexShader(IDirect3DVertexShader9* pShader)
{
	return m_pIDirect3DDevice9->SetVertexShader(pShader);
}

HRESULT cIDirect3DDevice9::GetVertexShader(IDirect3DVertexShader9** ppShader)
{
	return m_pIDirect3DDevice9->GetVertexShader(ppShader);
}

HRESULT cIDirect3DDevice9::SetVertexShaderConstantF(UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount)
{
	return m_pIDirect3DDevice9->SetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT cIDirect3DDevice9::GetVertexShaderConstantF(UINT StartRegister, float* pConstantData, UINT Vector4fCount)
{
	return m_pIDirect3DDevice9->GetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT cIDirect3DDevice9::SetVertexShaderConstantI(UINT StartRegister, CONST int* pConstantData, UINT Vector4iCount)
{
	return m_pIDirect3DDevice9->SetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT cIDirect3DDevice9::GetVertexShaderConstantI(UINT StartRegister, int* pConstantData, UINT Vector4iCount)
{
	return m_pIDirect3DDevice9->GetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT cIDirect3DDevice9::SetVertexShaderConstantB(UINT StartRegister, CONST BOOL* pConstantData, UINT  BoolCount)
{
	return m_pIDirect3DDevice9->SetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT cIDirect3DDevice9::GetVertexShaderConstantB(UINT StartRegister, BOOL* pConstantData, UINT BoolCount)
{
	return m_pIDirect3DDevice9->GetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT  cIDirect3DDevice9::SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride)
{
	return m_pIDirect3DDevice9->SetStreamSource(StreamNumber, pStreamData, OffsetInBytes, Stride);
}

HRESULT cIDirect3DDevice9::GetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9** ppStreamData, UINT* pOffsetInBytes, UINT* pStride)
{
	return m_pIDirect3DDevice9->GetStreamSource(StreamNumber, ppStreamData, pOffsetInBytes, pStride);
}

HRESULT cIDirect3DDevice9::SetStreamSourceFreq(UINT StreamNumber, UINT Setting)
{
	return m_pIDirect3DDevice9->SetStreamSourceFreq(StreamNumber, Setting);
}

HRESULT cIDirect3DDevice9::GetStreamSourceFreq(UINT StreamNumber, UINT* pSetting)
{
	return m_pIDirect3DDevice9->GetStreamSourceFreq(StreamNumber, pSetting);
}

HRESULT cIDirect3DDevice9::SetIndices(IDirect3DIndexBuffer9* pIndexData)
{
	return m_pIDirect3DDevice9->SetIndices(pIndexData);
}

HRESULT cIDirect3DDevice9::GetIndices(IDirect3DIndexBuffer9** ppIndexData)
{
	return m_pIDirect3DDevice9->GetIndices(ppIndexData);
}

HRESULT cIDirect3DDevice9::CreatePixelShader(CONST DWORD* pFunction, IDirect3DPixelShader9** ppShader)
{
	return m_pIDirect3DDevice9->CreatePixelShader(pFunction, ppShader);
}

HRESULT cIDirect3DDevice9::SetPixelShader(IDirect3DPixelShader9* pShader)
{
	return m_pIDirect3DDevice9->SetPixelShader(pShader);
}

HRESULT cIDirect3DDevice9::GetPixelShader(IDirect3DPixelShader9** ppShader)
{
	return m_pIDirect3DDevice9->GetPixelShader(ppShader);
}

HRESULT cIDirect3DDevice9::SetPixelShaderConstantF(UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount)
{
	return m_pIDirect3DDevice9->SetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT cIDirect3DDevice9::GetPixelShaderConstantF(UINT StartRegister, float* pConstantData, UINT Vector4fCount)
{
	return m_pIDirect3DDevice9->GetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT cIDirect3DDevice9::SetPixelShaderConstantI(UINT StartRegister, CONST int* pConstantData, UINT Vector4iCount)
{
	return m_pIDirect3DDevice9->SetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT cIDirect3DDevice9::GetPixelShaderConstantI(UINT StartRegister, int* pConstantData, UINT Vector4iCount)
{
	return m_pIDirect3DDevice9->GetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT cIDirect3DDevice9::SetPixelShaderConstantB(UINT StartRegister, CONST BOOL* pConstantData, UINT  BoolCount)
{
	return m_pIDirect3DDevice9->SetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT cIDirect3DDevice9::GetPixelShaderConstantB(UINT StartRegister, BOOL* pConstantData, UINT BoolCount)
{
	return m_pIDirect3DDevice9->GetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT cIDirect3DDevice9::DrawRectPatch(UINT Handle, CONST float* pNumSegs, CONST D3DRECTPATCH_INFO* pRectPatchInfo)
{
	return m_pIDirect3DDevice9->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
}

HRESULT cIDirect3DDevice9::DrawTriPatch(UINT Handle, CONST float* pNumSegs, CONST D3DTRIPATCH_INFO* pTriPatchInfo)
{
	return m_pIDirect3DDevice9->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
}

HRESULT cIDirect3DDevice9::DeletePatch(UINT Handle)
{
	return m_pIDirect3DDevice9->DeletePatch(Handle);
}

HRESULT cIDirect3DDevice9::CreateQuery(D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery)
{
	return m_pIDirect3DDevice9->CreateQuery(Type, ppQuery);
}




//----
// Ex
//----


cIDirect3DDevice9Ex::cIDirect3DDevice9Ex(IDirect3DDevice9Ex* pOriginal, bool showLogs, std::stringstream* log) :
																					m_pIDirect3DDevice9Ex(pOriginal),
																					doLog(showLogs),
																					logError(log),
																					isSet(false),
																					m_nRefCount(1)
{
	isSet = true;
	//*logError << "cIDirect3DDevice9Ex Construct" << std::endl;
}

cIDirect3DDevice9Ex::~cIDirect3DDevice9Ex()
{
	isSet = false;
	if (m_pIDirect3DDevice9Ex)
		m_pIDirect3DDevice9Ex->Release();
	//*logError << "cIDirect3DDevice9Ex Destruct" << std::endl;
}

HRESULT cIDirect3DDevice9Ex::QueryInterface(REFIID riid, LPVOID* ppv)
{
	return m_pIDirect3DDevice9Ex->QueryInterface(riid, ppv);
}

ULONG cIDirect3DDevice9Ex::AddRef()
{
	return ++m_nRefCount;
}

ULONG cIDirect3DDevice9Ex::Release()
{
	if (--m_nRefCount == 0)
	{
		delete this;
		return 0;
	}

	return m_nRefCount;
}

HRESULT cIDirect3DDevice9Ex::TestCooperativeLevel()
{
	return m_pIDirect3DDevice9Ex->TestCooperativeLevel();
}

UINT cIDirect3DDevice9Ex::GetAvailableTextureMem()
{
	return m_pIDirect3DDevice9Ex->GetAvailableTextureMem();
}

HRESULT cIDirect3DDevice9Ex::EvictManagedResources()
{
	return m_pIDirect3DDevice9Ex->EvictManagedResources();
}

HRESULT cIDirect3DDevice9Ex::GetDirect3D(IDirect3D9** ppD3D9)
{
	return m_pIDirect3DDevice9Ex->GetDirect3D(ppD3D9);
}

HRESULT cIDirect3DDevice9Ex::GetDeviceCaps(D3DCAPS9* pCaps)
{
	return m_pIDirect3DDevice9Ex->GetDeviceCaps(pCaps);
}

HRESULT cIDirect3DDevice9Ex::GetDisplayMode(UINT iSwapChain, D3DDISPLAYMODE* pMode)
{
	return m_pIDirect3DDevice9Ex->GetDisplayMode(iSwapChain, pMode);
}

HRESULT cIDirect3DDevice9Ex::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS* pParameters)
{
	return m_pIDirect3DDevice9Ex->GetCreationParameters(pParameters);
}

HRESULT cIDirect3DDevice9Ex::SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9* pCursorBitmap)
{
	return m_pIDirect3DDevice9Ex->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap);
}

void cIDirect3DDevice9Ex::SetCursorPosition(int X, int Y, DWORD Flags)
{
	return m_pIDirect3DDevice9Ex->SetCursorPosition(X, Y, Flags);
}

BOOL cIDirect3DDevice9Ex::ShowCursor(BOOL bShow)
{
	return m_pIDirect3DDevice9Ex->ShowCursor(bShow);
}

HRESULT cIDirect3DDevice9Ex::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain9** pSwapChain)
{
	return m_pIDirect3DDevice9Ex->CreateAdditionalSwapChain(pPresentationParameters, pSwapChain);
}

HRESULT cIDirect3DDevice9Ex::GetSwapChain(UINT iSwapChain, IDirect3DSwapChain9** pSwapChain)
{
	return m_pIDirect3DDevice9Ex->GetSwapChain(iSwapChain, pSwapChain);
}

UINT cIDirect3DDevice9Ex::GetNumberOfSwapChains()
{
	return m_pIDirect3DDevice9Ex->GetNumberOfSwapChains();
}

HRESULT cIDirect3DDevice9Ex::Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	return m_pIDirect3DDevice9Ex->Reset(pPresentationParameters);
}

HRESULT cIDirect3DDevice9Ex::Present(CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
	return m_pIDirect3DDevice9Ex->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

HRESULT cIDirect3DDevice9Ex::GetBackBuffer(UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9** ppBackBuffer)
{
	return m_pIDirect3DDevice9Ex->GetBackBuffer(iSwapChain, iBackBuffer, Type, ppBackBuffer);
}

HRESULT cIDirect3DDevice9Ex::GetRasterStatus(UINT iSwapChain, D3DRASTER_STATUS* pRasterStatus)
{
	return m_pIDirect3DDevice9Ex->GetRasterStatus(iSwapChain, pRasterStatus);
}

HRESULT cIDirect3DDevice9Ex::SetDialogBoxMode(BOOL bEnableDialogs)
{
	return m_pIDirect3DDevice9Ex->SetDialogBoxMode(bEnableDialogs);
}

void cIDirect3DDevice9Ex::SetGammaRamp(UINT iSwapChain, DWORD Flags, CONST D3DGAMMARAMP* pRamp)
{
	return m_pIDirect3DDevice9Ex->SetGammaRamp(iSwapChain, Flags, pRamp);
}

void cIDirect3DDevice9Ex::GetGammaRamp(UINT iSwapChain, D3DGAMMARAMP* pRamp)
{
	return m_pIDirect3DDevice9Ex->GetGammaRamp(iSwapChain, pRamp);
}

HRESULT cIDirect3DDevice9Ex::CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle)
{
	if (Usage == 0) { Usage = D3DUSAGE_DYNAMIC; }
	if (Pool == D3DPOOL_MANAGED) { Pool = D3DPOOL_DEFAULT; }
	return m_pIDirect3DDevice9Ex->CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);

	/*HRESULT result = m_pIDirect3DDevice9Ex->CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);
	if (Pool == D3DPOOL_DEFAULT && Levels == 1 && Format == 26)
	{
		std::ofstream ofOut("texture.txt", std::ios_base::app);
		ofOut << "CreateTexture - result: " << result << ", Width: " << Width << ", Height: " << Height << ", Levels: " << Levels << ", Usage: " << getUsageType(Usage) << ", Format: " << getFormatType(Format) << ", Pool: " << getPoolType(Pool) << ", ppTexture: " << *ppTexture << ", pSharedHandle: " << pSharedHandle << std::endl;
		ofOut.close();
	}
	return result;*/
}

HRESULT cIDirect3DDevice9Ex::CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9** ppVolumeTexture, HANDLE* pSharedHandle)
{
	if (Usage == 0) { Usage = D3DUSAGE_DYNAMIC; }
	if (Pool == D3DPOOL_MANAGED) { Pool = D3DPOOL_DEFAULT; }
	return m_pIDirect3DDevice9Ex->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);
}

HRESULT cIDirect3DDevice9Ex::CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture, HANDLE* pSharedHandle)
{
	if (Usage == 0) { Usage = D3DUSAGE_DYNAMIC; }
	if (Pool == D3DPOOL_MANAGED) { Pool = D3DPOOL_DEFAULT; }
	return m_pIDirect3DDevice9Ex->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle);
}

HRESULT cIDirect3DDevice9Ex::CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle)
{
	if (Usage == 0) { Usage = D3DUSAGE_DYNAMIC; }
	if (Pool == D3DPOOL_MANAGED) { Pool = D3DPOOL_DEFAULT; }
	return m_pIDirect3DDevice9Ex->CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);
}

HRESULT cIDirect3DDevice9Ex::CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle)
{
	if (Usage == 0) { Usage = D3DUSAGE_DYNAMIC; }
	if (Pool == D3DPOOL_MANAGED) { Pool = D3DPOOL_DEFAULT; }
	return m_pIDirect3DDevice9Ex->CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);
}

HRESULT cIDirect3DDevice9Ex::CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	return m_pIDirect3DDevice9Ex->CreateRenderTarget(Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle);
}

HRESULT cIDirect3DDevice9Ex::CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	return m_pIDirect3DDevice9Ex->CreateDepthStencilSurface(Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle);
}

HRESULT cIDirect3DDevice9Ex::UpdateSurface(IDirect3DSurface9* pSourceSurface, CONST RECT* pSourceRect, IDirect3DSurface9* pDestinationSurface, CONST POINT* pDestPoint)
{
	return m_pIDirect3DDevice9Ex->UpdateSurface(pSourceSurface, pSourceRect, pDestinationSurface, pDestPoint);
}

HRESULT cIDirect3DDevice9Ex::UpdateTexture(IDirect3DBaseTexture9* pSourceTexture, IDirect3DBaseTexture9* pDestinationTexture)
{
	return m_pIDirect3DDevice9Ex->UpdateTexture(pSourceTexture, pDestinationTexture);
}

HRESULT cIDirect3DDevice9Ex::GetRenderTargetData(IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface)
{
	return m_pIDirect3DDevice9Ex->GetRenderTargetData(pRenderTarget, pDestSurface);
}

HRESULT cIDirect3DDevice9Ex::GetFrontBufferData(UINT iSwapChain, IDirect3DSurface9* pDestSurface)
{
	return m_pIDirect3DDevice9Ex->GetFrontBufferData(iSwapChain, pDestSurface);
}

HRESULT cIDirect3DDevice9Ex::StretchRect(IDirect3DSurface9* pSourceSurface, CONST RECT* pSourceRect, IDirect3DSurface9* pDestSurface, CONST RECT* pDestRect, D3DTEXTUREFILTERTYPE Filter)
{
	return m_pIDirect3DDevice9Ex->StretchRect(pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter);
}

HRESULT cIDirect3DDevice9Ex::ColorFill(IDirect3DSurface9* pSurface, CONST RECT* pRect, D3DCOLOR color)
{
	return m_pIDirect3DDevice9Ex->ColorFill(pSurface, pRect, color);
}

HRESULT cIDirect3DDevice9Ex::CreateOffscreenPlainSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	if (Pool == D3DPOOL_MANAGED) { Pool = D3DPOOL_DEFAULT; }
	return m_pIDirect3DDevice9Ex->CreateOffscreenPlainSurface(Width, Height, Format, Pool, ppSurface, pSharedHandle);
}

HRESULT cIDirect3DDevice9Ex::SetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9* pRenderTarget)
{
	return m_pIDirect3DDevice9Ex->SetRenderTarget(RenderTargetIndex, pRenderTarget);
}

HRESULT cIDirect3DDevice9Ex::GetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9** ppRenderTarget)
{
	return m_pIDirect3DDevice9Ex->GetRenderTarget(RenderTargetIndex, ppRenderTarget);
}

HRESULT cIDirect3DDevice9Ex::SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil)
{
	return m_pIDirect3DDevice9Ex->SetDepthStencilSurface(pNewZStencil);
}

HRESULT cIDirect3DDevice9Ex::GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface)
{
	return m_pIDirect3DDevice9Ex->GetDepthStencilSurface(ppZStencilSurface);
}

HRESULT cIDirect3DDevice9Ex::BeginScene()
{
	return m_pIDirect3DDevice9Ex->BeginScene();
}

HRESULT cIDirect3DDevice9Ex::EndScene()
{
	return m_pIDirect3DDevice9Ex->EndScene();
}

HRESULT cIDirect3DDevice9Ex::Clear(DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
{
	return m_pIDirect3DDevice9Ex->Clear(Count, pRects, Flags, Color, Z, Stencil);
}

HRESULT cIDirect3DDevice9Ex::SetTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix)
{
	return m_pIDirect3DDevice9Ex->SetTransform(State, pMatrix);
}

HRESULT cIDirect3DDevice9Ex::GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix)
{
	return m_pIDirect3DDevice9Ex->GetTransform(State, pMatrix);
}

HRESULT cIDirect3DDevice9Ex::MultiplyTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix)
{
	return m_pIDirect3DDevice9Ex->MultiplyTransform(State, pMatrix);
}

HRESULT cIDirect3DDevice9Ex::SetViewport(CONST D3DVIEWPORT9* pViewport)
{
	return m_pIDirect3DDevice9Ex->SetViewport(pViewport);
}

HRESULT cIDirect3DDevice9Ex::GetViewport(D3DVIEWPORT9* pViewport)
{
	return m_pIDirect3DDevice9Ex->GetViewport(pViewport);
}

HRESULT cIDirect3DDevice9Ex::SetMaterial(CONST D3DMATERIAL9* pMaterial)
{
	return m_pIDirect3DDevice9Ex->SetMaterial(pMaterial);
}

HRESULT cIDirect3DDevice9Ex::GetMaterial(D3DMATERIAL9* pMaterial)
{
	return m_pIDirect3DDevice9Ex->GetMaterial(pMaterial);
}

HRESULT cIDirect3DDevice9Ex::SetLight(DWORD Index, CONST D3DLIGHT9* pLight)
{
	return m_pIDirect3DDevice9Ex->SetLight(Index, pLight);
}

HRESULT cIDirect3DDevice9Ex::GetLight(DWORD Index, D3DLIGHT9* pLight)
{
	return m_pIDirect3DDevice9Ex->GetLight(Index, pLight);
}

HRESULT cIDirect3DDevice9Ex::LightEnable(DWORD Index, BOOL Enable)
{
	return m_pIDirect3DDevice9Ex->LightEnable(Index, Enable);
}

HRESULT cIDirect3DDevice9Ex::GetLightEnable(DWORD Index, BOOL* pEnable)
{
	return m_pIDirect3DDevice9Ex->GetLightEnable(Index, pEnable);
}

HRESULT cIDirect3DDevice9Ex::SetClipPlane(DWORD Index, CONST float* pPlane)
{
	return m_pIDirect3DDevice9Ex->SetClipPlane(Index, pPlane);
}

HRESULT cIDirect3DDevice9Ex::GetClipPlane(DWORD Index, float* pPlane)
{
	return m_pIDirect3DDevice9Ex->GetClipPlane(Index, pPlane);
}

HRESULT cIDirect3DDevice9Ex::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
	return m_pIDirect3DDevice9Ex->SetRenderState(State, Value);
}

HRESULT cIDirect3DDevice9Ex::GetRenderState(D3DRENDERSTATETYPE State, DWORD* pValue)
{
	return m_pIDirect3DDevice9Ex->GetRenderState(State, pValue);
}

HRESULT cIDirect3DDevice9Ex::CreateStateBlock(D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9** ppSB)
{
	return m_pIDirect3DDevice9Ex->CreateStateBlock(Type, ppSB);
}

HRESULT cIDirect3DDevice9Ex::BeginStateBlock()
{
	return m_pIDirect3DDevice9Ex->BeginStateBlock();
}

HRESULT cIDirect3DDevice9Ex::EndStateBlock(IDirect3DStateBlock9** ppSB)
{
	return m_pIDirect3DDevice9Ex->EndStateBlock(ppSB);
}

HRESULT cIDirect3DDevice9Ex::SetClipStatus(CONST D3DCLIPSTATUS9* pClipStatus)
{
	return m_pIDirect3DDevice9Ex->SetClipStatus(pClipStatus);
}

HRESULT cIDirect3DDevice9Ex::GetClipStatus(D3DCLIPSTATUS9* pClipStatus)
{
	return m_pIDirect3DDevice9Ex->GetClipStatus(pClipStatus);
}

HRESULT cIDirect3DDevice9Ex::GetTexture(DWORD Stage, IDirect3DBaseTexture9** ppTexture)
{
	return m_pIDirect3DDevice9Ex->GetTexture(Stage, ppTexture);
}

HRESULT cIDirect3DDevice9Ex::SetTexture(DWORD Stage, IDirect3DBaseTexture9* pTexture)
{
	return m_pIDirect3DDevice9Ex->SetTexture(Stage, pTexture);
}

HRESULT cIDirect3DDevice9Ex::GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue)
{
	return m_pIDirect3DDevice9Ex->GetTextureStageState(Stage, Type, pValue);
}

HRESULT cIDirect3DDevice9Ex::SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)
{
	return m_pIDirect3DDevice9Ex->SetTextureStageState(Stage, Type, Value);
}

HRESULT cIDirect3DDevice9Ex::GetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD* pValue)
{
	return m_pIDirect3DDevice9Ex->GetSamplerState(Sampler, Type, pValue);
}

HRESULT cIDirect3DDevice9Ex::SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value)
{
	return m_pIDirect3DDevice9Ex->SetSamplerState(Sampler, Type, Value);
}

HRESULT cIDirect3DDevice9Ex::ValidateDevice(DWORD* pNumPasses)
{
	return m_pIDirect3DDevice9Ex->ValidateDevice(pNumPasses);
}

HRESULT cIDirect3DDevice9Ex::SetPaletteEntries(UINT PaletteNumber, CONST PALETTEENTRY* pEntries)
{
	return m_pIDirect3DDevice9Ex->SetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT cIDirect3DDevice9Ex::GetPaletteEntries(UINT PaletteNumber, PALETTEENTRY* pEntries)
{
	return m_pIDirect3DDevice9Ex->GetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT cIDirect3DDevice9Ex::SetCurrentTexturePalette(UINT PaletteNumber)
{
	return m_pIDirect3DDevice9Ex->SetCurrentTexturePalette(PaletteNumber);
}

HRESULT cIDirect3DDevice9Ex::GetCurrentTexturePalette(UINT* PaletteNumber)
{
	return m_pIDirect3DDevice9Ex->GetCurrentTexturePalette(PaletteNumber);
}

HRESULT cIDirect3DDevice9Ex::SetScissorRect(CONST RECT* pRect)
{
	return m_pIDirect3DDevice9Ex->SetScissorRect(pRect);
}

HRESULT cIDirect3DDevice9Ex::GetScissorRect(RECT* pRect)
{
	return m_pIDirect3DDevice9Ex->GetScissorRect(pRect);
}

HRESULT cIDirect3DDevice9Ex::SetSoftwareVertexProcessing(BOOL bSoftware)
{
	return m_pIDirect3DDevice9Ex->SetSoftwareVertexProcessing(bSoftware);
}

BOOL cIDirect3DDevice9Ex::GetSoftwareVertexProcessing()
{
	return m_pIDirect3DDevice9Ex->GetSoftwareVertexProcessing();
}

HRESULT cIDirect3DDevice9Ex::SetNPatchMode(float nSegments)
{
	return m_pIDirect3DDevice9Ex->SetNPatchMode(nSegments);
}

float cIDirect3DDevice9Ex::GetNPatchMode()
{
	return m_pIDirect3DDevice9Ex->GetNPatchMode();
}

HRESULT cIDirect3DDevice9Ex::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
	return m_pIDirect3DDevice9Ex->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}

HRESULT cIDirect3DDevice9Ex::DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
	return m_pIDirect3DDevice9Ex->DrawIndexedPrimitive(PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

HRESULT cIDirect3DDevice9Ex::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return m_pIDirect3DDevice9Ex->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT cIDirect3DDevice9Ex::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, CONST void* pIndexData, D3DFORMAT IndexDataFormat, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return m_pIDirect3DDevice9Ex->DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT cIDirect3DDevice9Ex::ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9* pDestBuffer, IDirect3DVertexDeclaration9* pVertexDecl, DWORD Flags)
{
	return m_pIDirect3DDevice9Ex->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags);
}

HRESULT cIDirect3DDevice9Ex::CreateVertexDeclaration(CONST D3DVERTEXELEMENT9* pVertexElements, IDirect3DVertexDeclaration9** ppDecl)
{
	return m_pIDirect3DDevice9Ex->CreateVertexDeclaration(pVertexElements, ppDecl);
}

HRESULT cIDirect3DDevice9Ex::SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl)
{
	return m_pIDirect3DDevice9Ex->SetVertexDeclaration(pDecl);
}

HRESULT cIDirect3DDevice9Ex::GetVertexDeclaration(IDirect3DVertexDeclaration9** ppDecl)
{
	return m_pIDirect3DDevice9Ex->GetVertexDeclaration(ppDecl);
}

HRESULT cIDirect3DDevice9Ex::SetFVF(DWORD FVF)
{
	return m_pIDirect3DDevice9Ex->SetFVF(FVF);
}

HRESULT cIDirect3DDevice9Ex::GetFVF(DWORD* pFVF)
{
	return m_pIDirect3DDevice9Ex->GetFVF(pFVF);
}

HRESULT cIDirect3DDevice9Ex::CreateVertexShader(CONST DWORD* pFunction, IDirect3DVertexShader9** ppShader)
{
	return m_pIDirect3DDevice9Ex->CreateVertexShader(pFunction, ppShader);
}

HRESULT cIDirect3DDevice9Ex::SetVertexShader(IDirect3DVertexShader9* pShader)
{
	return m_pIDirect3DDevice9Ex->SetVertexShader(pShader);
}

HRESULT cIDirect3DDevice9Ex::GetVertexShader(IDirect3DVertexShader9** ppShader)
{
	return m_pIDirect3DDevice9Ex->GetVertexShader(ppShader);
}

HRESULT cIDirect3DDevice9Ex::SetVertexShaderConstantF(UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount)
{
	return m_pIDirect3DDevice9Ex->SetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT cIDirect3DDevice9Ex::GetVertexShaderConstantF(UINT StartRegister, float* pConstantData, UINT Vector4fCount)
{
	return m_pIDirect3DDevice9Ex->GetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT cIDirect3DDevice9Ex::SetVertexShaderConstantI(UINT StartRegister, CONST int* pConstantData, UINT Vector4iCount)
{
	return m_pIDirect3DDevice9Ex->SetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT cIDirect3DDevice9Ex::GetVertexShaderConstantI(UINT StartRegister, int* pConstantData, UINT Vector4iCount)
{
	return m_pIDirect3DDevice9Ex->GetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT cIDirect3DDevice9Ex::SetVertexShaderConstantB(UINT StartRegister, CONST BOOL* pConstantData, UINT  BoolCount)
{
	return m_pIDirect3DDevice9Ex->SetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT cIDirect3DDevice9Ex::GetVertexShaderConstantB(UINT StartRegister, BOOL* pConstantData, UINT BoolCount)
{
	return m_pIDirect3DDevice9Ex->GetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT  cIDirect3DDevice9Ex::SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride)
{
	return m_pIDirect3DDevice9Ex->SetStreamSource(StreamNumber, pStreamData, OffsetInBytes, Stride);
}

HRESULT cIDirect3DDevice9Ex::GetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9** ppStreamData, UINT* pOffsetInBytes, UINT* pStride)
{
	return m_pIDirect3DDevice9Ex->GetStreamSource(StreamNumber, ppStreamData, pOffsetInBytes, pStride);
}

HRESULT cIDirect3DDevice9Ex::SetStreamSourceFreq(UINT StreamNumber, UINT Setting)
{
	return m_pIDirect3DDevice9Ex->SetStreamSourceFreq(StreamNumber, Setting);
}

HRESULT cIDirect3DDevice9Ex::GetStreamSourceFreq(UINT StreamNumber, UINT* pSetting)
{
	return m_pIDirect3DDevice9Ex->GetStreamSourceFreq(StreamNumber, pSetting);
}

HRESULT cIDirect3DDevice9Ex::SetIndices(IDirect3DIndexBuffer9* pIndexData)
{
	return m_pIDirect3DDevice9Ex->SetIndices(pIndexData);
}

HRESULT cIDirect3DDevice9Ex::GetIndices(IDirect3DIndexBuffer9** ppIndexData)
{
	return m_pIDirect3DDevice9Ex->GetIndices(ppIndexData);
}

HRESULT cIDirect3DDevice9Ex::CreatePixelShader(CONST DWORD* pFunction, IDirect3DPixelShader9** ppShader)
{
	return m_pIDirect3DDevice9Ex->CreatePixelShader(pFunction, ppShader);
}

HRESULT cIDirect3DDevice9Ex::SetPixelShader(IDirect3DPixelShader9* pShader)
{
	return m_pIDirect3DDevice9Ex->SetPixelShader(pShader);
}

HRESULT cIDirect3DDevice9Ex::GetPixelShader(IDirect3DPixelShader9** ppShader)
{
	return m_pIDirect3DDevice9Ex->GetPixelShader(ppShader);
}

HRESULT cIDirect3DDevice9Ex::SetPixelShaderConstantF(UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount)
{
	return m_pIDirect3DDevice9Ex->SetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT cIDirect3DDevice9Ex::GetPixelShaderConstantF(UINT StartRegister, float* pConstantData, UINT Vector4fCount)
{
	return m_pIDirect3DDevice9Ex->GetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT cIDirect3DDevice9Ex::SetPixelShaderConstantI(UINT StartRegister, CONST int* pConstantData, UINT Vector4iCount)
{
	return m_pIDirect3DDevice9Ex->SetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT cIDirect3DDevice9Ex::GetPixelShaderConstantI(UINT StartRegister, int* pConstantData, UINT Vector4iCount)
{
	return m_pIDirect3DDevice9Ex->GetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT cIDirect3DDevice9Ex::SetPixelShaderConstantB(UINT StartRegister, CONST BOOL* pConstantData, UINT  BoolCount)
{
	return m_pIDirect3DDevice9Ex->SetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT cIDirect3DDevice9Ex::GetPixelShaderConstantB(UINT StartRegister, BOOL* pConstantData, UINT BoolCount)
{
	return m_pIDirect3DDevice9Ex->GetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT cIDirect3DDevice9Ex::DrawRectPatch(UINT Handle, CONST float* pNumSegs, CONST D3DRECTPATCH_INFO* pRectPatchInfo)
{
	return m_pIDirect3DDevice9Ex->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
}

HRESULT cIDirect3DDevice9Ex::DrawTriPatch(UINT Handle, CONST float* pNumSegs, CONST D3DTRIPATCH_INFO* pTriPatchInfo)
{
	return m_pIDirect3DDevice9Ex->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
}

HRESULT cIDirect3DDevice9Ex::DeletePatch(UINT Handle)
{
	return m_pIDirect3DDevice9Ex->DeletePatch(Handle);
}

HRESULT cIDirect3DDevice9Ex::CreateQuery(D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery)
{
	return m_pIDirect3DDevice9Ex->CreateQuery(Type, ppQuery);
}

HRESULT cIDirect3DDevice9Ex::SetConvolutionMonoKernel(UINT width, UINT height, float* rows, float* columns)
{
	return m_pIDirect3DDevice9Ex->SetConvolutionMonoKernel(width, height, rows, columns);
}

HRESULT cIDirect3DDevice9Ex::ComposeRects(IDirect3DSurface9* pSrc, IDirect3DSurface9* pDst, IDirect3DVertexBuffer9* pSrcRectDescs, UINT NumRects, IDirect3DVertexBuffer9* pDstRectDescs, D3DCOMPOSERECTSOP Operation, int Xoffset, int Yoffset)
{
	return m_pIDirect3DDevice9Ex->ComposeRects(pSrc, pDst, pSrcRectDescs, NumRects, pDstRectDescs, Operation, Xoffset, Yoffset);
}

HRESULT cIDirect3DDevice9Ex::PresentEx(CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion, DWORD dwFlags)
{
	return m_pIDirect3DDevice9Ex->PresentEx(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion, dwFlags);
}

HRESULT cIDirect3DDevice9Ex::GetGPUThreadPriority(INT* pPriority)
{
	return m_pIDirect3DDevice9Ex->GetGPUThreadPriority(pPriority);
}

HRESULT cIDirect3DDevice9Ex::SetGPUThreadPriority(INT Priority)
{
	return m_pIDirect3DDevice9Ex->SetGPUThreadPriority(Priority);
}

HRESULT cIDirect3DDevice9Ex::WaitForVBlank(UINT iSwapChain)
{
	return m_pIDirect3DDevice9Ex->WaitForVBlank(iSwapChain);
}

HRESULT cIDirect3DDevice9Ex::CheckResourceResidency(IDirect3DResource9** pResourceArray, UINT32 NumResources)
{
	return m_pIDirect3DDevice9Ex->CheckResourceResidency(pResourceArray, NumResources);
}

HRESULT cIDirect3DDevice9Ex::SetMaximumFrameLatency(UINT MaxLatency)
{
	return m_pIDirect3DDevice9Ex->SetMaximumFrameLatency(MaxLatency);
}

HRESULT cIDirect3DDevice9Ex::GetMaximumFrameLatency(UINT* pMaxLatency)
{
	return m_pIDirect3DDevice9Ex->GetMaximumFrameLatency(pMaxLatency);
}

HRESULT cIDirect3DDevice9Ex::CheckDeviceState(HWND hDestinationWindow)
{
	return m_pIDirect3DDevice9Ex->CheckDeviceState(hDestinationWindow);
}

HRESULT cIDirect3DDevice9Ex::CreateRenderTargetEx(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle, DWORD Usage)
{
	return m_pIDirect3DDevice9Ex->CreateRenderTargetEx(Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle, Usage);
}

HRESULT cIDirect3DDevice9Ex::CreateOffscreenPlainSurfaceEx(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle, DWORD Usage)
{
	return m_pIDirect3DDevice9Ex->CreateOffscreenPlainSurfaceEx(Width, Height, Format, Pool, ppSurface, pSharedHandle, Usage);
}

HRESULT cIDirect3DDevice9Ex::CreateDepthStencilSurfaceEx(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle, DWORD Usage)
{
	return m_pIDirect3DDevice9Ex->CreateDepthStencilSurfaceEx(Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle, Usage);
}

HRESULT cIDirect3DDevice9Ex::ResetEx(D3DPRESENT_PARAMETERS* pPresentationParameters, D3DDISPLAYMODEEX* pFullscreenDisplayMode)
{
	return m_pIDirect3DDevice9Ex->ResetEx(pPresentationParameters, pFullscreenDisplayMode);
}

HRESULT cIDirect3DDevice9Ex::GetDisplayModeEx(UINT iSwapChain, D3DDISPLAYMODEEX* pMode, D3DDISPLAYROTATION* pRotation)
{
	return m_pIDirect3DDevice9Ex->GetDisplayModeEx(iSwapChain, pMode, pRotation);
}
