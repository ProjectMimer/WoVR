#include "cShaderData.h"

VertexShaderTexture::VertexShaderTexture()
{
	AddLayout({ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 });
	AddLayout({ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 });
	AddLayout(D3DDECL_END());
	SetSource("VShader", "vs_3_0", R"""(
struct VOut
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};
matrix projectionMatrix : register(c0);
matrix viewMatrix : register(c4);
matrix worldMatrix : register(c8);

VOut VShader(float4 position : SV_POSITION, float2 tex : TEXCOORD0)
{
	VOut output;
	output.position = float4(position.xyz, 1.0f);
	output.position = mul(output.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);
	output.tex = tex;
	return output;
}
)""");
}