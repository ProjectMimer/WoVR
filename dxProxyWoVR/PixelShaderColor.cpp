#include "cShaderData.h"

PixelShaderColor::PixelShaderColor()
{
	SetSource("PShaderColor", "ps_3_0", R"""(
struct VOutColor
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

float4 PShaderColor(VOutColor input) : SV_TARGET
{
	return input.color;
}
)""");
};