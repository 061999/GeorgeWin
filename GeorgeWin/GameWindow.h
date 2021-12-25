#pragma once
#include <Windows.h>
#include <d3d11.h>
#include "GameTimer.h"

class GameWindow
{
public:
	GameWindow(HINSTANCE hinst);
	bool Init();
	int Run();
	LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
private:
	bool InitWindow();
	bool InitDirectX();
	void setFPS();
private:
	void RenderScene();
	void EndRender();
	void ClearScene(float red, float green, float blue);
private:
	GameTimer mTimer;
	HINSTANCE gamehInst;
	LPCWSTR	  gameClassName;
	HWND	  gamehWnd;
private:
	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwap = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
	ID3D11RenderTargetView* pTarget = nullptr;
};

