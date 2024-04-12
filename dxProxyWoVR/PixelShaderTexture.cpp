#include "cShaderData.h"

PixelShaderTexture::PixelShaderTexture()
{
	SetSource("PShaderTexture", "ps_3_0", R"""(
sampler sam0 : register(s0);

struct VOut
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};

float4 PShaderTexture(VOut input) : SV_TARGET
{
	return tex2D(sam0, input.tex);
}
)""");
};