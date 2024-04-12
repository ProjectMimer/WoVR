#include "cRenderObject.h"

RenderOSK::RenderOSK(IDirect3DDevice9* tdev) : RenderObject(tdev)
{
	std::vector<float> vertices =
	{
		 -1, -1, 0,		0, 1,
		 -1,  1, 0,		0, 0,
		  1,  1, 0,		1, 0,
		  1, -1, 0,		1, 1,
	};
	SetVertexBuffer(vertices, 5);


	std::vector<short> indices =
	{
		0, 1, 2,
		2, 3, 0
	};
	SetIndexBuffer(indices);
}