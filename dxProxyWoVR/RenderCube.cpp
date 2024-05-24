#include "cRenderObject.h"

RenderCube::RenderCube(IDirect3DDevice9* tdev) : RenderObject(tdev)
{
	if (tdev == nullptr)
		return;

	std::vector<float> vertices =
	{
		 -0.55f, -0.55f, -0.55f,   0.0f, 0.0f, 0.0f, 1.0f,
		 -0.55f,  0.55f, -0.55f,   0.0f, 0.0f, 1.0f, 1.0f,
		  0.55f,  0.55f, -0.55f,   0.0f, 1.0f, 0.0f, 1.0f,
		  0.55f, -0.55f, -0.55f,   0.0f, 1.0f, 1.0f, 1.0f,
		 -0.55f, -0.55f,  0.55f,   1.0f, 0.0f, 0.0f, 1.0f,
		 -0.55f,  0.55f,  0.55f,   1.0f, 0.0f, 1.0f, 1.0f,
		  0.55f,  0.55f,  0.55f,   1.0f, 1.0f, 0.0f, 1.0f,
		  0.55f, -0.55f,  0.55f,   1.0f, 1.0f, 1.0f, 1.0f,
	};
	SetVertexBuffer(vertices, 7);

	//   5----6
	//  /|   /|
	// 1----2 |
	// | 4--|-7
	// |/   |/
	// 0----3
	//

	std::vector<short> indices =
	{
		// front face
		0, 1, 2,
		0, 2, 3,

		// back face
		7, 6, 5,
		7, 5, 4,

		// left face
		4, 5, 1,
		4, 1, 0,

		// right face
		3, 2, 6,
		3, 6, 7,

		// top face
		1, 5, 6,
		1, 6, 2,

		// bottom face
		4, 0, 3,
		4, 3, 7
	};
	SetIndexBuffer(indices);
}