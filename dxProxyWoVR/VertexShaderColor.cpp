#include "cShaderData.h"

VertexShaderColor::VertexShaderColor()
{
	AddLayout({ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 });
	AddLayout({ 0, 12, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 });
	AddLayout(D3DDECL_END());
	SetSource("VShaderColor", "vs_3_0", R"""(
struct VOutColor
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};
matrix projectionMatrix : register(c0);
matrix viewMatrix : register(c4);
matrix worldMatrix : register(c8);

VOutColor VShaderColor(float4 position : SV_POSITION, float4 color : COLOR)
{
	VOutColor output;
    output.position = float4(position.xyz, 1.0f);
	output.position = mul(output.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);
	output.color = color;
	return output;
}
)""");
};