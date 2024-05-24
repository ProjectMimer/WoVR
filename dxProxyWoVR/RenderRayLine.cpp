#include "cRenderObject.h"

RenderRayLine::RenderRayLine(IDirect3DDevice9* tdev) : RenderObject(tdev)
{
	if (tdev == nullptr)
		return;

	std::vector<float> vertices =
	{
		0, 0, 1,		1.0f, 0.0f, 0.0f, 0.75f,
		0, 0,-1,		0.0f, 0.0f, 1.0f, 0.25f
	};
	SetVertexBuffer(vertices, 7);
}
