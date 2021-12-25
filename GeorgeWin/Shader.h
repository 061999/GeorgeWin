#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
class Shader
{
public:
	Shader();
	Shader(const wchar_t* vertexShaderPath, const wchar_t* pixelShaderPath);
	Shader(const wchar_t* vertexShaderPath, const wchar_t* pixelShaderPath, ID3D11Device* pDevice);

	void LoadVertexShader(const wchar_t* vertexShaderPath);
	void LoadPixelShader(const wchar_t* pixelShaderPath);
	void CreateVertexShader(ID3D11Device* pDevice);
	void CreatePixelShader(ID3D11Device* pDevice);
	void SetVertexShader(ID3D11DeviceContext* pContext);
	void SetPixelShader(ID3D11DeviceContext* pContext);
	void SetAllShader(ID3D11DeviceContext* pContext);
public:
	ID3DBlob* LayoutBlob = nullptr;
private:
	ID3D11VertexShader* pVertexShader = nullptr;
	ID3D11PixelShader* pPixelShader = nullptr;
	ID3DBlob* pVertexBlob = nullptr;
	ID3DBlob* pPixelBlob = nullptr;
};

