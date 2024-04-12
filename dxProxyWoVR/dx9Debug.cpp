#include "dx9Debug.h"

std::string getRendStateType(D3DRENDERSTATETYPE State)
{
	switch (State)
	{
	case   7: return "D3DRS_ZENABLE"; break;
	case   8: return "D3DRS_FILLMODE"; break;
	case   9: return "D3DRS_SHADEMODE"; break;
	case  14: return "D3DRS_ZWRITEENABLE"; break;
	case  15: return "D3DRS_ALPHATESTENABLE"; break;
	case  16: return "D3DRS_LASTPIXEL"; break;
	case  19: return "D3DRS_SRCBLEND"; break;
	case  20: return "D3DRS_DESTBLEND"; break;
	case  22: return "D3DRS_CULLMODE"; break;
	case  23: return "D3DRS_ZFUNC"; break;
	case  24: return "D3DRS_ALPHAREF"; break;
	case  25: return "D3DRS_ALPHAFUNC"; break;
	case  26: return "D3DRS_DITHERENABLE"; break;
	case  27: return "D3DRS_ALPHABLENDENABLE"; break;
	case  28: return "D3DRS_FOGENABLE"; break;
	case  29: return "D3DRS_SPECULARENABLE"; break;
	case  34: return "D3DRS_FOGCOLOR"; break;
	case  35: return "D3DRS_FOGTABLEMODE"; break;
	case  36: return "D3DRS_FOGSTART"; break;
	case  37: return "D3DRS_FOGEND"; break;
	case  38: return "D3DRS_FOGDENSITY"; break;
	case  48: return "D3DRS_RANGEFOGENABLE"; break;
	case  52: return "D3DRS_STENCILENABLE"; break;
	case  53: return "D3DRS_STENCILFAIL"; break;
	case  54: return "D3DRS_STENCILZFAIL"; break;
	case  55: return "D3DRS_STENCILPASS"; break;
	case  56: return "D3DRS_STENCILFUNC"; break;
	case  57: return "D3DRS_STENCILREF"; break;
	case  58: return "D3DRS_STENCILMASK"; break;
	case  59: return "D3DRS_STENCILWRITEMASK"; break;
	case  60: return "D3DRS_TEXTUREFACTOR"; break;
	case 128: return "D3DRS_WRAP0"; break;
	case 129: return "D3DRS_WRAP1"; break;
	case 130: return "D3DRS_WRAP2"; break;
	case 131: return "D3DRS_WRAP3"; break;
	case 132: return "D3DRS_WRAP4"; break;
	case 133: return "D3DRS_WRAP5"; break;
	case 134: return "D3DRS_WRAP6"; break;
	case 135: return "D3DRS_WRAP7"; break;
	case 136: return "D3DRS_CLIPPING"; break;
	case 137: return "D3DRS_LIGHTING"; break;
	case 139: return "D3DRS_AMBIENT"; break;
	case 140: return "D3DRS_FOGVERTEXMODE"; break;
	case 141: return "D3DRS_COLORVERTEX"; break;
	case 142: return "D3DRS_LOCALVIEWER"; break;
	case 143: return "D3DRS_NORMALIZENORMALS"; break;
	case 145: return "D3DRS_DIFFUSEMATERIALSOURCE"; break;
	case 146: return "D3DRS_SPECULARMATERIALSOURCE"; break;
	case 147: return "D3DRS_AMBIENTMATERIALSOURCE"; break;
	case 148: return "D3DRS_EMISSIVEMATERIALSOURCE"; break;
	case 151: return "D3DRS_VERTEXBLEND"; break;
	case 152: return "D3DRS_CLIPPLANEENABLE"; break;
	case 154: return "D3DRS_POINTSIZE"; break;
	case 155: return "D3DRS_POINTSIZE_MIN"; break;
	case 156: return "D3DRS_POINTSPRITEENABLE"; break;
	case 157: return "D3DRS_POINTSCALEENABLE"; break;
	case 158: return "D3DRS_POINTSCALE_A"; break;
	case 159: return "D3DRS_POINTSCALE_B"; break;
	case 160: return "D3DRS_POINTSCALE_C"; break;
	case 161: return "D3DRS_MULTISAMPLEANTIALIAS"; break;
	case 162: return "D3DRS_MULTISAMPLEMASK"; break;
	case 163: return "D3DRS_PATCHEDGESTYLE"; break;
	case 165: return "D3DRS_DEBUGMONITORTOKEN"; break;
	case 166: return "D3DRS_POINTSIZE_MAX"; break;
	case 167: return "D3DRS_INDEXEDVERTEXBLENDENABLE"; break;
	case 168: return "D3DRS_COLORWRITEENABLE"; break;
	case 170: return "D3DRS_TWEENFACTOR"; break;
	case 171: return "D3DRS_BLENDOP"; break;
	case 172: return "D3DRS_POSITIONDEGREE"; break;
	case 173: return "D3DRS_NORMALDEGREE"; break;
	case 174: return "D3DRS_SCISSORTESTENABLE"; break;
	case 175: return "D3DRS_SLOPESCALEDEPTHBIAS"; break;
	case 176: return "D3DRS_ANTIALIASEDLINEENABLE"; break;
	case 178: return "D3DRS_MINTESSELLATIONLEVEL"; break;
	case 179: return "D3DRS_MAXTESSELLATIONLEVEL"; break;
	case 180: return "D3DRS_ADAPTIVETESS_X"; break;
	case 181: return "D3DRS_ADAPTIVETESS_Y"; break;
	case 182: return "D3DRS_ADAPTIVETESS_Z"; break;
	case 183: return "D3DRS_ADAPTIVETESS_W"; break;
	case 184: return "D3DRS_ENABLEADAPTIVETESSELLATION"; break;
	case 185: return "D3DRS_TWOSIDEDSTENCILMODE"; break;
	case 186: return "D3DRS_CCW_STENCILFAIL"; break;
	case 187: return "D3DRS_CCW_STENCILZFAIL"; break;
	case 188: return "D3DRS_CCW_STENCILPASS"; break;
	case 189: return "D3DRS_CCW_STENCILFUNC"; break;
	case 190: return "D3DRS_COLORWRITEENABLE1"; break;
	case 191: return "D3DRS_COLORWRITEENABLE2"; break;
	case 192: return "D3DRS_COLORWRITEENABLE3"; break;
	case 193: return "D3DRS_BLENDFACTOR"; break;
	case 194: return "D3DRS_SRGBWRITEENABLE"; break;
	case 195: return "D3DRS_DEPTHBIAS"; break;
	case 198: return "D3DRS_WRAP8"; break;
	case 199: return "D3DRS_WRAP9"; break;
	case 200: return "D3DRS_WRAP10"; break;
	case 201: return "D3DRS_WRAP11"; break;
	case 202: return "D3DRS_WRAP12"; break;
	case 203: return "D3DRS_WRAP13"; break;
	case 204: return "D3DRS_WRAP14"; break;
	case 205: return "D3DRS_WRAP15"; break;
	case 206: return "D3DRS_SEPARATEALPHABLENDENABLE"; break;
	case 207: return "D3DRS_SRCBLENDALPHA"; break;
	case 208: return "D3DRS_DESTBLENDALPHA"; break;
	case 209: return "D3DRS_BLENDOPALPHA"; break;
	case 0x7fffffff: return "D3DRS_FORCE_DWORD"; break;
	default: return "?"; break;
	}
}

std::string getTransformStateType(D3DTRANSFORMSTATETYPE State)
{
	switch (State)
	{
	case 2: return "D3DTS_VIEW"; break;
	case 3: return "D3DTS_PROJECTION"; break;
	case 16: return "D3DTS_TEXTURE0"; break;
	case 17: return "D3DTS_TEXTURE1"; break;
	case 18: return "D3DTS_TEXTURE2"; break;
	case 19: return "D3DTS_TEXTURE3"; break;
	case 20: return "D3DTS_TEXTURE4"; break;
	case 21: return "D3DTS_TEXTURE5"; break;
	case 22: return "D3DTS_TEXTURE6"; break;
	case 23: return "D3DTS_TEXTURE7"; break;
	case 0x7fffffff: return "D3DTS_FORCE_DWORD"; break;
	default: return "?"; break;
	}
}

std::string getSamplerStateType(D3DSAMPLERSTATETYPE State)
{
	switch (State)
	{
	case 1: return "D3DSAMP_ADDRESSU"; break;
	case 2: return "D3DSAMP_ADDRESSV"; break;
	case 3: return "D3DSAMP_ADDRESSW"; break;
	case 4: return "D3DSAMP_BORDERCOLOR"; break;
	case 5: return "D3DSAMP_MAGFILTER"; break;
	case 6: return "D3DSAMP_MINFILTER"; break;
	case 7: return "D3DSAMP_MIPFILTER"; break;
	case 8: return "D3DSAMP_MIPMAPLODBIAS"; break;
	case 9: return "D3DSAMP_MAXMIPLEVEL"; break;
	case 10: return "D3DSAMP_MAXANISOTROPY"; break;
	case 11: return "D3DSAMP_SRGBTEXTURE"; break;
	case 12: return "D3DSAMP_ELEMENTINDEX"; break;
	case 13: return "D3DSAMP_DMAPOFFSET"; break;
	case 0x7fffffff: return "D3DSAMP_FORCE_DWORD"; break;
	default: return "?"; break;
	}
}

std::string getTextureStageStateType(D3DTEXTURESTAGESTATETYPE State)
{
	switch (State)
	{
	case 1: return "D3DTSS_COLOROP"; break;
	case 2: return "D3DTSS_COLORARG1"; break;
	case 3: return "D3DTSS_COLORARG2"; break;
	case 4: return "D3DTSS_ALPHAOP"; break;
	case 5: return "D3DTSS_ALPHAARG1"; break;
	case 6: return "D3DTSS_ALPHAARG2"; break;
	case 7: return "D3DTSS_BUMPENVMAT00"; break;
	case 8: return "D3DTSS_BUMPENVMAT01"; break;
	case 9: return "D3DTSS_BUMPENVMAT10"; break;
	case 10: return "D3DTSS_BUMPENVMAT11"; break;
	case 11: return "D3DTSS_TEXCOORDINDEX"; break;
	case 22: return "D3DTSS_BUMPENVLSCALE"; break;
	case 23: return "D3DTSS_BUMPENVLOFFSET"; break;
	case 24: return "D3DTSS_TEXTURETRANSFORMFLAGS"; break;
	case 26: return "D3DTSS_COLORARG0"; break;
	case 27: return "D3DTSS_ALPHAARG0"; break;
	case 28: return "D3DTSS_RESULTARG"; break;
	case 32: return "D3DTSS_CONSTANT"; break;
	case 0x7fffffff: return "D3DTSS_FORCE_DWORD"; break;
	default: return "?"; break;
	}
}


std::string getFormatType(D3DFORMAT Format)
{
	switch (Format)
	{
	case 0: return "D3DFMT_UNKNOWN"; break;
	case 20: return "D3DFMT_R8G8B8"; break;
	case 21: return "D3DFMT_A8R8G8B8"; break;
	case 22: return "D3DFMT_X8R8G8B8"; break;
	case 23: return "D3DFMT_R5G6B5"; break;
	case 24: return "D3DFMT_X1R5G5B5"; break;
	case 25: return "D3DFMT_A1R5G5B5"; break;
	case 26: return "D3DFMT_A4R4G4B4"; break;
	case 27: return "D3DFMT_R3G3B2"; break;
	case 28: return "D3DFMT_A8"; break;
	case 29: return "D3DFMT_A8R3G3B2"; break;
	case 30: return "D3DFMT_X4R4G4B4"; break;
	case 31: return "D3DFMT_A2B10G10R10"; break;
	case 32: return "D3DFMT_A8B8G8R8"; break;
	case 33: return "D3DFMT_X8B8G8R8"; break;
	case 34: return "D3DFMT_G16R16"; break;
	case 35: return "D3DFMT_A2R10G10B10"; break;
	case 36: return "D3DFMT_A16B16G16R16"; break;
	case 40: return "D3DFMT_A8P8"; break;
	case 41: return "D3DFMT_P8"; break;
	case 50: return "D3DFMT_L8"; break;
	case 51: return "D3DFMT_A8L8"; break;
	case 52: return "D3DFMT_A4L4"; break;
	case 60: return "D3DFMT_V8U8"; break;
	case 61: return "D3DFMT_L6V5U5"; break;
	case 62: return "D3DFMT_X8L8V8U8"; break;
	case 63: return "D3DFMT_Q8W8V8U8"; break;
	case 64: return "D3DFMT_V16U16"; break;
	case 67: return "D3DFMT_A2W10V10U10"; break;
	case MAKEFOURCC('U', 'Y', 'V', 'Y'): return "D3DFMT_UYVY"; break;
	case MAKEFOURCC('R', 'G', 'B', 'G'): return "D3DFMT_R8G8_B8G8"; break;
	case MAKEFOURCC('Y', 'U', 'Y', '2'): return "D3DFMT_YUY2"; break;
	case MAKEFOURCC('G', 'R', 'G', 'B'): return "D3DFMT_G8R8_G8B8"; break;
	case MAKEFOURCC('D', 'X', 'T', '1'): return "D3DFMT_DXT1"; break;
	case MAKEFOURCC('D', 'X', 'T', '2'): return "D3DFMT_DXT2"; break;
	case MAKEFOURCC('D', 'X', 'T', '3'): return "D3DFMT_DXT3"; break;
	case MAKEFOURCC('D', 'X', 'T', '4'): return "D3DFMT_DXT4"; break;
	case MAKEFOURCC('D', 'X', 'T', '5'): return "D3DFMT_DXT5"; break;
	case 70: return "D3DFMT_D16_LOCKABLE"; break;
	case 71: return "D3DFMT_D32"; break;
	case 73: return "D3DFMT_D15S1"; break;
	case 75: return "D3DFMT_D24S8"; break;
	case 77: return "D3DFMT_D24X8"; break;
	case 79: return "D3DFMT_D24X4S4"; break;
	case 80: return "D3DFMT_D16"; break;
	case 82: return "D3DFMT_D32F_LOCKABLE"; break;
	case 83: return "D3DFMT_D24FS8"; break;
	case 84: return "D3DFMT_D32_LOCKABLE"; break;
	case 85: return "D3DFMT_S8_LOCKABLE"; break;
	case 81: return "D3DFMT_L16"; break;
	case 100: return "D3DFMT_VERTEXDATA"; break;
	case 101: return "D3DFMT_INDEX16"; break;
	case 102: return "D3DFMT_INDEX32"; break;
	case 110: return "D3DFMT_Q16W16V16U16"; break;
	case MAKEFOURCC('M', 'E', 'T', '1'): return "D3DFMT_MULTI2_ARGB8"; break;
	case 111: return "D3DFMT_R16F"; break;
	case 112: return "D3DFMT_G16R16F"; break;
	case 113: return "D3DFMT_A16B16G16R16F"; break;
	case 114: return "D3DFMT_R32F"; break;
	case 115: return "D3DFMT_G32R32F"; break;
	case 116: return "D3DFMT_A32B32G32R32F"; break;
	case 117: return "D3DFMT_CxV8U8"; break;
	case 118: return "D3DFMT_A1"; break;
	case 119: return "D3DFMT_A2B10G10R10_XR_BIAS"; break;
	case 199: return "D3DFMT_BINARYBUFFER"; break;
	case 0x7fffffff: return "D3DFMT_FORCE_DWORD"; break;
	default: return "?"; break;
	}
}

std::string getPoolType(D3DPOOL Pool)
{
	switch (Pool)
	{
	case 0: return "D3DPOOL_DEFAULT"; break;
	case 1: return "D3DPOOL_MANAGED"; break;
	case 2: return "D3DPOOL_SYSTEMMEM"; break;
	case 3: return "D3DPOOL_SCRATCH"; break;
	case 0x7fffffff: return "D3DPOOL_FORCE_DWORD"; break;
	default: return "?"; break;
	}
}

std::string getUsageType(DWORD Usage)
{
	switch (Usage)
	{
	case 0x00000001L: return "D3DUSAGE_RENDERTARGET"; break;
	case 0x00000002L: return "D3DUSAGE_DEPTHSTENCIL"; break;
	case 0x00000200L: return "D3DUSAGE_DYNAMIC"; break;
	case 0x00800000L: return "D3DUSAGE_NONSECURE"; break;
	case 0x00000400L: return "D3DUSAGE_AUTOGENMIPMAP"; break;
	case 0x00004000L: return "D3DUSAGE_DMAP"; break;
	case 0x00008000L: return "D3DUSAGE_QUERY_LEGACYBUMPMAP"; break;
	case 0x00010000L: return "D3DUSAGE_QUERY_SRGBREAD"; break;
	case 0x00020000L: return "D3DUSAGE_QUERY_FILTER"; break;
	case 0x00040000L: return "D3DUSAGE_QUERY_SRGBWRITE"; break;
	case 0x00080000L: return "D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDIN"; break;
	case 0x00100000L: return "D3DUSAGE_QUERY_VERTEXTEXTURE"; break;
	case 0x00200000L: return "D3DUSAGE_QUERY_WRAPANDMIP"; break;
	case 0x00000008L: return "D3DUSAGE_WRITEONLY"; break;
	case 0x00000010L: return "D3DUSAGE_SOFTWAREPROCESSING"; break;
	case 0x00000020L: return "D3DUSAGE_DONOTCLIP"; break;
	case 0x00000040L: return "D3DUSAGE_POINTS"; break;
	case 0x00000080L: return "D3DUSAGE_RTPATCHES"; break;
	case 0x00000100L: return "D3DUSAGE_NPATCHES"; break;
	case 0x10000000L: return "D3DUSAGE_TEXTAPI"; break;
	case 0x00000800L: return "D3DUSAGE_RESTRICTED_CONTENT"; break;
	case 0x00002000L: return "D3DUSAGE_RESTRICT_SHARED_RESOURCE"; break;
	case 0x00001000L: return "D3DUSAGE_RESTRICT_SHARED_RESOURCE_DRIVER"; break;
	default: return "?"; break;
	}
}

std::string getPrimitiveType(D3DPRIMITIVETYPE PrimitiveType)
{
	switch (PrimitiveType)
	{
	case 1: return "D3DPT_POINTLIST"; break;
	case 2: return "D3DPT_LINELIST"; break;
	case 3: return "D3DPT_LINESTRIP"; break;
	case 4: return "D3DPT_TRIANGLELIST"; break;
	case 5: return "D3DPT_TRIANGLESTRIP"; break;
	case 6: return "D3DPT_TRIANGLEFAN"; break;
	case 0x7fffffff: return "D3DPT_FORCE_DWORD"; break;
	default: return "?"; break;
	}
}


std::string getDeclType(BYTE Type)
{
	switch (Type)
	{
	case 0: return "D3DDECLTYPE_FLOAT1"; break;
	case 1: return "D3DDECLTYPE_FLOAT2"; break;
	case 2: return "D3DDECLTYPE_FLOAT3"; break;
	case 3: return "D3DDECLTYPE_FLOAT4"; break;
	case 4: return "D3DDECLTYPE_D3DCOLOR"; break;
	case 5: return "D3DDECLTYPE_UBYTE4"; break;
	case 6: return "D3DDECLTYPE_SHORT2"; break;
	case 7: return "D3DDECLTYPE_SHORT4"; break;
	case 8: return "D3DDECLTYPE_UBYTE4N"; break;
	case 9: return "D3DDECLTYPE_SHORT2N"; break;
	case 10: return "D3DDECLTYPE_SHORT4N"; break;
	case 11: return "D3DDECLTYPE_USHORT2N"; break;
	case 12: return "D3DDECLTYPE_USHORT4N"; break;
	case 13: return "D3DDECLTYPE_UDEC3"; break;
	case 14: return "D3DDECLTYPE_DEC3N"; break;
	case 15: return "D3DDECLTYPE_FLOAT16_2"; break;
	case 16: return "D3DDECLTYPE_FLOAT16_4"; break;
	case 17: return "D3DDECLTYPE_UNUSED"; break;
	default: return "?"; break;
	}
}

std::string getDeclMethod(BYTE Method)
{
	switch (Method)
	{
	case 0: return "D3DDECLMETHOD_DEFAULT"; break;
	case 1: return "D3DDECLMETHOD_PARTIALU"; break;
	case 2: return "D3DDECLMETHOD_PARTIALV"; break;
	case 3: return "D3DDECLMETHOD_CROSSUV"; break;
	case 4: return "D3DDECLMETHOD_UV"; break;
	case 5: return "D3DDECLMETHOD_LOOKUP"; break;
	case 6: return "D3DDECLMETHOD_LOOKUPPRESAMPLED"; break;
	default: return "?"; break;
	}
}

std::string getDeclUsage(BYTE Usage)
{
	switch (Usage)
	{
	case 0: return "D3DDECLUSAGE_POSITION"; break;
	case 1: return "D3DDECLUSAGE_BLENDWEIGHT"; break;
	case 2: return "D3DDECLUSAGE_BLENDINDICES"; break;
	case 3: return "D3DDECLUSAGE_NORMAL"; break;
	case 4: return "D3DDECLUSAGE_PSIZE"; break;
	case 5: return "D3DDECLUSAGE_TEXCOORD"; break;
	case 6: return "D3DDECLUSAGE_TANGENT"; break;
	case 7: return "D3DDECLUSAGE_BINORMAL"; break;
	case 8: return "D3DDECLUSAGE_TESSFACTOR"; break;
	case 9: return "D3DDECLUSAGE_POSITIONT"; break;
	case 10: return "D3DDECLUSAGE_COLOR"; break;
	case 11: return "D3DDECLUSAGE_FOG"; break;
	case 12: return "D3DDECLUSAGE_DEPTH"; break;
	case 13: return "D3DDECLUSAGE_SAMPLE"; break;
	default: return "?"; break;
	}
}

static rendStat CurRendStates[] = {
		rendStat(D3DRS_ZENABLE), //0
		rendStat(D3DRS_FILLMODE),
		rendStat(D3DRS_SHADEMODE),
		rendStat(D3DRS_ZWRITEENABLE),
		rendStat(D3DRS_ALPHATESTENABLE),
		rendStat(D3DRS_LASTPIXEL),
		rendStat(D3DRS_SRCBLEND),
		rendStat(D3DRS_DESTBLEND),
		rendStat(D3DRS_CULLMODE),
		rendStat(D3DRS_ZFUNC),
		rendStat(D3DRS_ALPHAREF), //10
		rendStat(D3DRS_ALPHAFUNC),
		rendStat(D3DRS_DITHERENABLE),
		rendStat(D3DRS_ALPHABLENDENABLE),
		rendStat(D3DRS_FOGENABLE),
		rendStat(D3DRS_SPECULARENABLE),
		rendStat(D3DRS_FOGCOLOR),
		rendStat(D3DRS_FOGTABLEMODE),
		rendStat(D3DRS_FOGSTART),
		rendStat(D3DRS_FOGEND),
		rendStat(D3DRS_FOGDENSITY), //20
		rendStat(D3DRS_RANGEFOGENABLE),
		rendStat(D3DRS_STENCILENABLE),
		rendStat(D3DRS_STENCILFAIL),
		rendStat(D3DRS_STENCILZFAIL),
		rendStat(D3DRS_STENCILPASS),
		rendStat(D3DRS_STENCILFUNC),
		rendStat(D3DRS_STENCILREF),
		rendStat(D3DRS_STENCILMASK),
		rendStat(D3DRS_STENCILWRITEMASK),
		rendStat(D3DRS_TEXTUREFACTOR), //30
		rendStat(D3DRS_WRAP0),
		rendStat(D3DRS_WRAP1),
		rendStat(D3DRS_WRAP2),
		rendStat(D3DRS_WRAP3),
		rendStat(D3DRS_WRAP4),
		rendStat(D3DRS_WRAP5),
		rendStat(D3DRS_WRAP6),
		rendStat(D3DRS_WRAP7),
		rendStat(D3DRS_CLIPPING),
		rendStat(D3DRS_LIGHTING), //40
		rendStat(D3DRS_AMBIENT),
		rendStat(D3DRS_FOGVERTEXMODE),
		rendStat(D3DRS_COLORVERTEX),
		rendStat(D3DRS_LOCALVIEWER),
		rendStat(D3DRS_NORMALIZENORMALS),
		rendStat(D3DRS_DIFFUSEMATERIALSOURCE),
		rendStat(D3DRS_SPECULARMATERIALSOURCE),
		rendStat(D3DRS_AMBIENTMATERIALSOURCE),
		rendStat(D3DRS_EMISSIVEMATERIALSOURCE),
		rendStat(D3DRS_VERTEXBLEND), //50
		rendStat(D3DRS_CLIPPLANEENABLE),
		rendStat(D3DRS_POINTSIZE),
		rendStat(D3DRS_POINTSIZE_MIN),
		rendStat(D3DRS_POINTSPRITEENABLE),
		rendStat(D3DRS_POINTSCALEENABLE),
		rendStat(D3DRS_POINTSCALE_A),
		rendStat(D3DRS_POINTSCALE_B),
		rendStat(D3DRS_POINTSCALE_C),
		rendStat(D3DRS_MULTISAMPLEANTIALIAS),
		rendStat(D3DRS_MULTISAMPLEMASK), //60
		rendStat(D3DRS_PATCHEDGESTYLE),
		rendStat(D3DRS_DEBUGMONITORTOKEN),
		rendStat(D3DRS_POINTSIZE_MAX),
		rendStat(D3DRS_INDEXEDVERTEXBLENDENABLE),
		rendStat(D3DRS_COLORWRITEENABLE),
		rendStat(D3DRS_TWEENFACTOR),
		rendStat(D3DRS_BLENDOP),
		rendStat(D3DRS_POSITIONDEGREE),
		rendStat(D3DRS_NORMALDEGREE),
		rendStat(D3DRS_SCISSORTESTENABLE), //70
		rendStat(D3DRS_SLOPESCALEDEPTHBIAS),
		rendStat(D3DRS_ANTIALIASEDLINEENABLE),
		rendStat(D3DRS_MINTESSELLATIONLEVEL),
		rendStat(D3DRS_MAXTESSELLATIONLEVEL),
		rendStat(D3DRS_ADAPTIVETESS_X),
		rendStat(D3DRS_ADAPTIVETESS_Y),
		rendStat(D3DRS_ADAPTIVETESS_Z),
		rendStat(D3DRS_ADAPTIVETESS_W),
		rendStat(D3DRS_ENABLEADAPTIVETESSELLATION),
		rendStat(D3DRS_TWOSIDEDSTENCILMODE), //80
		rendStat(D3DRS_CCW_STENCILFAIL),
		rendStat(D3DRS_CCW_STENCILZFAIL),
		rendStat(D3DRS_CCW_STENCILPASS),
		rendStat(D3DRS_CCW_STENCILFUNC),
		rendStat(D3DRS_COLORWRITEENABLE1),
		rendStat(D3DRS_COLORWRITEENABLE2),
		rendStat(D3DRS_COLORWRITEENABLE3),
		rendStat(D3DRS_BLENDFACTOR),
		rendStat(D3DRS_SRGBWRITEENABLE),
		rendStat(D3DRS_DEPTHBIAS), //90
		rendStat(D3DRS_WRAP8),
		rendStat(D3DRS_WRAP9),
		rendStat(D3DRS_WRAP10),
		rendStat(D3DRS_WRAP11),
		rendStat(D3DRS_WRAP12),
		rendStat(D3DRS_WRAP13),
		rendStat(D3DRS_WRAP14),
		rendStat(D3DRS_WRAP15),
		rendStat(D3DRS_SEPARATEALPHABLENDENABLE),
		rendStat(D3DRS_SRCBLENDALPHA), //100
		rendStat(D3DRS_DESTBLENDALPHA),
		rendStat(D3DRS_BLENDOPALPHA)
};

// Save the current render states
void SaveOriginalStates(IDirect3DDevice9* dxDev, bool runFindChanges)
{
	int numItems = sizeof(CurRendStates) / sizeof(rendStat);
	for (int i = 0; i < numItems; i++) {
		CurRendStates[i].index = i;
		dxDev->GetRenderState(CurRendStates[i].item, &CurRendStates[i].curStat);
		if (runFindChanges == false) {
			CurRendStates[i].oldStat = CurRendStates[i].curStat;
		}
		CurRendStates[i].enabled = false;
		CurRendStates[i].newStat = 0;
	}
}

// Find the changes between render states
std::vector<rendStat> GetChangedStates(IDirect3DDevice9* dxDev, bool runFindChanges)
{
	std::vector<rendStat> changes = std::vector<rendStat>();
	if (runFindChanges == true) {
		int numItems = sizeof(CurRendStates) / sizeof(rendStat);
		for (int i = 0; i < numItems; i++) {
			if (CurRendStates[i].curStat != CurRendStates[i].oldStat) {
				//changes.push_back(rendStat(CurRendStates[i].item, CurRendStates[i].curStat, CurRendStates[i].oldStat, CurRendStates[i].enabled, CurRendStates[i].newStat));
				changes.push_back(CurRendStates[i]);
			}
		}
	}
	return changes;
}

// Loads the origional render states
void LoadOriginalStates(IDirect3DDevice9* dxDev)
{
	int numItems = sizeof(CurRendStates) / sizeof(rendStat);
	for (int i = 0; i < numItems; i++) {
		dxDev->SetRenderState(CurRendStates[i].item, CurRendStates[i].curStat);
	}
}

// Loads the new render states
void LoadNewStates(IDirect3DDevice9* dxDev)
{
	int numItems = sizeof(CurRendStates) / sizeof(rendStat);
	for (int i = 0; i < numItems; i++) {
		if (CurRendStates[i].enabled) {
			dxDev->SetRenderState(CurRendStates[i].item, CurRendStates[i].newStat);
		}
	}
}

// Sets a new render state value
void SetNewStates(int index, DWORD value)
{
	CurRendStates[index].newStat = value; CurRendStates[index].enabled = true;
}
