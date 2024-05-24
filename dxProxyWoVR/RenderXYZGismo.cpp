#include "cRenderObject.h"

RenderXYZGizmo::RenderXYZGizmo(IDirect3DDevice9* tdev) : RenderObject(tdev)
{
	if (tdev == nullptr)
		return;

	std::vector<float> vertices =
	{
		// x,y,z
		-1, 0, 0,		1.0f, 0.0f, 0.0f, 1.0f,
		 1, 0, 0,		1.0f, 0.0f, 0.0f, 1.0f,
		 0,-1, 0,		1.0f, 0.0f, 0.0f, 1.0f,
		 0, 1, 0,		1.0f, 0.0f, 0.0f, 1.0f,
		 0, 0,-1,		1.0f, 0.0f, 0.0f, 1.0f,
		 0, 0, 1,		1.0f, 0.0f, 0.0f, 1.0f,

		 // diagonal
		-1, 1, 1,		1.0f, 0.0f, 0.0f, 1.0f,
		 1,-1,-1,		1.0f, 0.0f, 0.0f, 1.0f,
		-1, 1,-1,		1.0f, 0.0f, 0.0f, 1.0f,
		 1,-1, 1,		1.0f, 0.0f, 0.0f, 1.0f,
		 1, 1, 1,		1.0f, 0.0f, 0.0f, 1.0f,
		-1,-1,-1,		1.0f, 0.0f, 0.0f, 1.0f,
		 1, 1,-1,		1.0f, 0.0f, 0.0f, 1.0f,
		-1,-1, 1,		1.0f, 0.0f, 0.0f, 1.0f,

	};
	SetVertexBuffer(vertices, 7);
}
