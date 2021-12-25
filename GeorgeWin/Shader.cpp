#include "Shader.h"

Shader::Shader()
{
}

Shader::Shader(const wchar_t* vertexShaderPath, const wchar_t* pixelShaderPath)
{
	LoadVertexShader(vertexShaderPath);
	LoadPixelShader(pixelShaderPath);
}

Shader::Shader(const wchar_t* vertexShaderPath, const wchar_t* pixelShaderPath, ID3D11Device* pDevice)
{
	LoadVertexShader(vertexShaderPath);
	LoadPixelShader(pixelShaderPath);
	CreateVertexShader(pDevice);
	CreatePixelShader(pDevice);
}



void Shader::LoadVertexShader(const wchar_t* vertexShaderPath)
{
	D3DReadFileToBlob(vertexShaderPath, &pVertexBlob);
	this->LayoutBlob = this->pVertexBlob;
}

void Shader::LoadPixelShader(const wchar_t* pixelShaderPath)
{
	D3DReadFileToBlob(pixelShaderPath, &pPixelBlob);
}

void Shader::CreateVertexShader(ID3D11Device* pDevice)
{
	pDevice->CreateVertexShader(pVertexBlob->GetBufferPointer(), pVertexBlob->GetBufferSize(), nullptr, &pVertexShader);
}

void Shader::CreatePixelShader(ID3D11Device* pDevice)
{
	pDevice->CreatePixelShader(pPixelBlob->GetBufferPointer(), pPixelBlob->GetBufferSize(), nullptr, &pPixelShader);
}

void Shader::SetVertexShader(ID3D11DeviceContext* pContext)
{
	pContext->VSSetShader(pVertexShader, nullptr, 0u);
}

void Shader::SetPixelShader(ID3D11DeviceContext* pContext)
{
	pContext->PSSetShader(pPixelShader, nullptr, 0u);
}

void Shader::SetAllShader(ID3D11DeviceContext* pContext)
{
	pContext->VSSetShader(pVertexShader, nullptr, 0u);
	pContext->PSSetShader(pPixelShader, nullptr, 0u);
}
