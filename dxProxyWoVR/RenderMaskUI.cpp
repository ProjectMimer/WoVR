#include "cRenderObject.h"

RenderMaskUI::RenderMaskUI(IDirect3DDevice9* tdev) : RenderObject(tdev)
{
	if (tdev == nullptr)
		return;

	std::vector<float> vertices =
	{
		 -1, -1,  0,	0, 1,
		 -1,  1,  0,	0, 0,
		  1,  1,  0,	1, 0,
		  1, -1,  0,    1, 1
	};
	SetVertexBuffer(vertices, 5);


	std::vector<short> indices =
	{
		0, 1, 2,
		0, 2, 3
	};
	SetIndexBuffer(indices);
}
