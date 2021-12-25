#pragma once
#include <d3d11.h>
#include "Shader.h"
class InputLayout
{
public:
	InputLayout(ID3D11Device* device, ID3D11DeviceContext* context, Shader* s);
private:
	ID3D11InputLayout* pInputLayout = nullptr;
	ID3D11Device* pDevice = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
};

