#include "cRenderObject.h"


RenderObject::RenderObject() : dev(nullptr)
{
}

RenderObject::RenderObject(IDirect3DDevice9* tdev) : dev(tdev)
{
}

bool RenderObject::SetVertexBuffer(std::vector<float> vertices, int itmStride, bool ignoreCreateBuffer, D3DPOOL usage)
{
	vertexList = vertices;
	stride = itmStride;
	byteStride = stride * sizeof(float);
	vertexCount = (int)vertices.size() / stride;
	int byteWidth = vertexCount * byteStride;
	
	vertexSet = false;
	if (vertices.size() > 0)
	{
		HRESULT result = S_OK;
		if (!ignoreCreateBuffer)
			result = dev->CreateVertexBuffer(vertices.size() * sizeof(float), D3DUSAGE_WRITEONLY, NULL, usage, &vertexBuffer, NULL);

		if (FAILED(result))
			return false;
		else
			MapResourceVertex(vertices.data(), vertices.size() * sizeof(float));
		vertexSet = true;
	}
	return vertexSet;
}

int RenderObject::GetVertexCount()
{
	return vertexCount;
}

bool RenderObject::SetIndexBuffer(std::vector<short> indices, bool ignoreCreateBuffer, D3DPOOL usage)
{
	indexList = indices;
	indexCount = (int)indices.size();
	int byteWidth = indexCount * sizeof(short);

	indexSet = false;
	if (indices.size() > 0)
	{
		HRESULT result = S_OK;
		if (!ignoreCreateBuffer)
			result = dev->CreateIndexBuffer(indices.size() * sizeof(short), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, usage, &indexBuffer, NULL);
		
		if (FAILED(result))
			return false;
		else
			MapResourceIndex(indices.data(), indices.size() * sizeof(short));
		indexSet = true;
	}
	return indexSet;
}

void RenderObject::SetShadersLayout(IDirect3DVertexDeclaration9* layout, IDirect3DVertexShader9* vertex, IDirect3DPixelShader9* pixel)
{
	structLayout = layout;
	vertexShader = vertex;
	pixelShader = pixel;
}

void RenderObject::MapResourceVertex(void* data, int size)
{
	void* pVoid;
	if (vertexBuffer)
	{
		vertexBuffer->Lock(0, 0, (void**)&pVoid, 0);
		memcpy(pVoid, data, size);
		vertexBuffer->Unlock();
	}
}

void RenderObject::MapResourceIndex(void* data, int size)
{
	void* pVoid;
	if (indexBuffer)
	{
		indexBuffer->Lock(0, 0, (void**)&pVoid, 0);
		memcpy(pVoid, data, size);
		indexBuffer->Unlock();
	}
}


bool RenderObject::RayIntersection(XMVECTOR origin, XMVECTOR direction, std::vector<intersectPoint>* intersection, std::vector<bool> interactable, std::stringstream* logError)
{
	bool intersected = false;
	//XMMATRIX objMatrixI = XMMatrixInverse(0, objMatrix);
	if (indexSet)
	{
		for (int i = 0, j = 0; i < indexCount; i += 3, j++)
		{
			int i0 = indexList[i + 0];
			int i1 = indexList[i + 1];
			int i2 = indexList[i + 2];

			XMVECTOR v0 = { vertexList[i0 * stride + 0], vertexList[i0 * stride + 1], vertexList[i0 * stride + 2] };
			XMVECTOR v1 = { vertexList[i1 * stride + 0], vertexList[i1 * stride + 1], vertexList[i1 * stride + 2] };
			XMVECTOR v2 = { vertexList[i2 * stride + 0], vertexList[i2 * stride + 1], vertexList[i2 * stride + 2] };

			XMVECTOR v0uv = { vertexList[i0 * stride + 3], vertexList[i0 * stride + 4], 1.0f };
			XMVECTOR v1uv = { vertexList[i1 * stride + 3], vertexList[i1 * stride + 4], 1.0f };
			XMVECTOR v2uv = { vertexList[i2 * stride + 3], vertexList[i2 * stride + 4], 1.0f };

			v0 = XMVector3Transform(v0, objMatrix);
			v1 = XMVector3Transform(v1, objMatrix);
			v2 = XMVector3Transform(v2, objMatrix);

			float pickU = 0.0f;
			float pickV = 0.0f;
			float pickW = 0.0f;
			float distance = 0.0f;

			bool isInteractable = ((interactable.size() > 0) ? ((interactable.size() > j) ? interactable[j] : false) : true);
			if (isInteractable)
			{
				bool rayHit = RayTest(origin, direction, v0, v1, v2, &pickU, &pickV, &pickW, &distance, logError);
				if (rayHit)
				{
					intersected = true;
					intersection->push_back(intersectPoint(distance, pickU * v1uv + pickV * v2uv + pickW * v0uv));
					//(*logError) << pickU << " : " << pickV << " : " << pickW << " : " << (*distance) << " -- " << intersection->m128_f32[0] << ", " <<intersection->m128_f32[1] << ", " << intersection->m128_f32[2] << std::endl;
				}
			}
		}
	}
	else
	{
		for (int i = 0, j = 0; i < vertexCount; i += 3, j++)
		{
			int i0 = (i + 0) * stride;
			int i1 = (i + 1) * stride;
			int i2 = (i + 2) * stride;

			XMVECTOR v0 = { vertexList[i0 + 0], vertexList[i0 + 1], vertexList[i0 + 2] };
			XMVECTOR v1 = { vertexList[i1 + 0], vertexList[i1 + 1], vertexList[i1 + 2] };
			XMVECTOR v2 = { vertexList[i2 + 0], vertexList[i2 + 1], vertexList[i2 + 2] };

			XMVECTOR v0uv = { vertexList[i0 + 3], vertexList[i0 + 4], 1.0f };
			XMVECTOR v1uv = { vertexList[i1 + 3], vertexList[i1 + 4], 1.0f };
			XMVECTOR v2uv = { vertexList[i2 + 3], vertexList[i2 + 4], 1.0f };

			v0 = XMVector3Transform(v0, objMatrix);
			v1 = XMVector3Transform(v1, objMatrix);
			v2 = XMVector3Transform(v2, objMatrix);

			float pickU = 0.0f;
			float pickV = 0.0f;
			float pickW = 0.0f;
			float distance = 0.0f;

			bool isInteractable = ((interactable.size() > 0) ? ((interactable.size() > j) ? interactable[j] : false) : true);
			if (isInteractable)
			{
				bool rayHit = RayTest(origin, direction, v0, v1, v2, &pickU, &pickV, &pickW, &distance, logError);
				if (rayHit)
				{
					intersected = true;
					intersection->push_back(intersectPoint(distance, pickU * v1uv + pickV * v2uv + pickW * v0uv));
					//(*logError) << pickU << " : " << pickV << " : " << pickW << " : " << (*distance) << " -- " << intersection->m128_f32[0] << ", " <<intersection->m128_f32[1] << ", " << intersection->m128_f32[2] << std::endl;
				}
			}
		}
	}
	return intersected;
}

bool RenderObject::RayTest(XMVECTOR origin, XMVECTOR direction, XMVECTOR v0, XMVECTOR v1, XMVECTOR v2, float* barycentricU, float* barycentricV, float* barycentricW, float* distance, std::stringstream* logError)
{
	XMVECTOR v1v0 = v1 - v0;
	XMVECTOR v2v0 = v2 - v0;
	XMVECTOR vOv0 = origin - v0;

	// Begin calculating determinant - also used to calculate barycentricU parameter
	XMVECTOR pvec = XMVector3Cross(direction, v2v0);

	// If determinant is near zero, ray lies in plane of triangle
	float det = 0;
	DirectX::XMStoreFloat(&det, XMVector3Dot(v1v0, pvec));
	if (det < 0.0001f && det > -0.0001f)
		return false;
	float fInvDet = 1.0f / det;

	// Calculate barycentricU parameter and test bounds
	DirectX::XMStoreFloat(barycentricU, XMVector3Dot(vOv0, pvec) * fInvDet);
	if (*barycentricU < 0.0f || *barycentricU > 1.0f)
		return false;

	// Prepare to test barycentricV parameter
	XMVECTOR qvec = XMVector3Cross(vOv0, v1v0);

	// Calculate barycentricV parameter and test bounds
	DirectX::XMStoreFloat(barycentricV, XMVector3Dot(direction, qvec) * fInvDet);
	if (*barycentricV < 0.0f || (*barycentricU + *barycentricV) > 1.0f)
		return false;

	// Calculate pickDistance
	DirectX::XMStoreFloat(distance, XMVector3Dot(v2v0, qvec) * fInvDet);
	if (*distance > 0)
		return false;
	(*barycentricW) = 1.f - (*barycentricU) - (*barycentricV);

	//(*logError) << det << " : " << fInvDet << " : " << (*barycentricU) << " : " << (*barycentricV) << " : " << (*distance) << std::endl;
	return true;

}

void RenderObject::Render(D3DPRIMITIVETYPE type, int start, int count)
{
	HRESULT result = S_OK;
	result = dev->SetVertexDeclaration(structLayout);
	result = dev->SetVertexShader(vertexShader);
	result = dev->SetPixelShader(pixelShader);
	int primitiveCount = 0;

	if (type == D3DPT_TRIANGLELIST && !indexSet)
		primitiveCount = vertexCount / 3;
	else if (type == D3DPT_TRIANGLELIST && indexSet)
		primitiveCount = indexCount / 3;
	else if(type == D3DPT_LINELIST)
		primitiveCount = vertexCount / 2;

	if (count > 0)
		primitiveCount = count;

	if (vertexSet)
		result = dev->SetStreamSource(0, vertexBuffer, 0, byteStride);
	
	if (indexSet)
	{
		result = dev->SetIndices(indexBuffer);
		result = dev->DrawIndexedPrimitive(type, 0, 0, primitiveCount, start, indexCount);
	}
	else
	{
		result = dev->DrawPrimitive(type, start, primitiveCount);
	}
}


void RenderObject::SetObjectMatrix(XMMATRIX matrix)
{
	objMatrix = matrix;
}

XMMATRIX RenderObject::GetObjectMatrix(bool inverse, bool transpose)
{
	if (transpose && inverse)
		return XMMatrixTranspose(XMMatrixInverse(0, objMatrix));
	else if (transpose)
		return XMMatrixTranspose(objMatrix);
	else if (inverse)
		return XMMatrixInverse(0, objMatrix);
	else
		return objMatrix;
}

void RenderObject::Release()
{
	if (vertexBuffer) { vertexBuffer->Release(); vertexBuffer = nullptr; }
	if (indexBuffer) { indexBuffer->Release(); indexBuffer = nullptr; }

	if (structLayout) { structLayout = nullptr; }
	if (vertexShader) { vertexShader = nullptr; }
	if (pixelShader) { pixelShader = nullptr; }

	vertexCount = 0;
	indexCount = 0;

	dev = nullptr;
}
