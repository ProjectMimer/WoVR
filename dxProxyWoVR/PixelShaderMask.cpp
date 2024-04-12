#include "cShaderData.h"

PixelShaderMask::PixelShaderMask()
{
	SetSource("PShaderMask", "ps_3_0", R"""(
sampler sam0 : register(s0);

struct VOut
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};

float4 PShaderMask(VOut input) : SV_TARGET
{
	float4 pixel = tex2D(sam0, input.tex);
	if(pixel[3] <= 0.05)
	{
		pixel = float4(0,0,0,1);
	}
	else
	{
		pixel = float4(1,1,1,1);
	}
	return pixel;
}
)""");
};