#pragma once
#include <d3d11.h>
#include "LoadModel.h"
class Buffer
{
public:
	Buffer(ID3D11Device* device, ID3D11DeviceContext* context);
	void BindModelData(LoadModel* mod);
private:
	ID3D11Buffer* pVertexBuffer = nullptr;
	ID3D11Buffer* pIndexBuffer = nullptr;
	ID3D11Device* pDevice = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
};

