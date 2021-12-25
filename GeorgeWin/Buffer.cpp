#include "Buffer.h"

Buffer::Buffer(ID3D11Device* device, ID3D11DeviceContext* context):
	pDevice(device),
	pContext(context)
{
}

void Buffer::BindModelData(LoadModel* mod)
{
#pragma region CreateAndBindIndexBuffer
	D3D11_BUFFER_DESC id = {};
	id.BindFlags = D3D11_BIND_INDEX_BUFFER;
	id.Usage = D3D11_USAGE_DEFAULT;
	id.CPUAccessFlags = 0u;
	id.MiscFlags = 0u;
	id.ByteWidth = sizeof(int) * mod->indexsize;
	id.StructureByteStride = sizeof(int);

	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = mod->index;

	pDevice->CreateBuffer(&id, &isd, &pIndexBuffer);//DXGI_FORMAT_R16_UINT
	pContext->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R32_UINT, 0u);
#pragma endregion

#pragma region CreateAndBindVertexBuffer
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = sizeof(float) * mod->vertexsize;
	bd.StructureByteStride = sizeof(float) * 5;

	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = mod->vertex;

	pDevice->CreateBuffer(&bd, &sd, &pVertexBuffer);

	const UINT stride = sizeof(float) * 5;
	const UINT offset = 0u;
	pContext->IASetVertexBuffers(0u, 1u, &pVertexBuffer, &stride, &offset);
#pragma endregion

}
