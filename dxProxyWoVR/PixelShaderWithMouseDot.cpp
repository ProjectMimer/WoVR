#include "cShaderData.h"

PixelShaderWithMouseDot::PixelShaderWithMouseDot()
{
	SetSource("PShader", "ps_3_0", R"""(
sampler sam0 : register(s0);
static const float PI = 3.14159265;
float2 radiusR;
float2 coordsR;
float2 radiusB;
float2 coordsB;

struct VOut
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};
float4 tex2Dmultisample(sampler tex, float2 uv)
{
	float2 dx = ddx(uv) * 0.25;
	float2 dy = ddy(uv) * 0.25;

	float4 sample0 = tex2D(tex, uv + dx + dy);
	float4 sample1 = tex2D(tex, uv + dx - dy);
	float4 sample2 = tex2D(tex, uv - dx + dy);
	float4 sample3 = tex2D(tex, uv - dx - dy);
    
	return (sample0 + sample1 + sample2 + sample3) * 0.25;
}
float4 PShader(VOut input) : SV_TARGET
{
	//return tex2D(sam0, input.tex);
	return tex2Dmultisample(sam0, input.tex);

	//float distanceR = length(input.tex - coordsR);
	//float distanceB = length(input.tex - coordsB);
	//float4 pixel = float4(0.0, 0.0, 0.0, 0.0);
	//if (distanceR <= radiusR.x)
	//{
	//	pixel = float4(1.0, 0.0, 0.0, 0.75);
	//}
	//else if (distanceB <= radiusB.x)
	//{
	//	pixel = float4(0.498, 0.0, 1.0, 1.0);
	//}
	//else
	//{
	//	pixel = tex2Dmultisample(texture0, input.tex);
	//}
	//return pixel;
}
)""");
};