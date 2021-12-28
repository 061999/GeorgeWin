#include "GameWindow.h"
#include <sstream>
#include "Buffer.h"
#include "InputLayout.h"
#include "LoadModel.h"
#include "Shader.h"
#include "resource.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

GameWindow* LPAPP=nullptr;


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
		return true;
	return LPAPP->MsgProc(hwnd, msg, wParam, lParam);
}

GameWindow::GameWindow(HINSTANCE hinst):
	gamehInst(hinst),
	gameClassName(L"D3DGame")
{
	LPAPP = this;
}

bool GameWindow::Init()
{
	if (!InitWindow())
	{
		return false;
	}
	if (!InitDirectX())
	{
		return false;
	}
	if (!InitImgui())
	{
		return false;
	}
	if (!InitWorld())
	{
		return false;
	}
	return true;
}

int GameWindow::Run()
{
	MSG msg = { 0 };

	mTimer.Reset();

	while (msg.message != WM_QUIT)
	{
		// If there are Window messages then process them.
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// Otherwise, do animation/game stuff.
		else
		{
			mTimer.Tick();
			ClearScene(0.5f, 0.6f, 0.7f);
			RenderScene();
			EndRender();
			setFPS();
		}
	}

	return (int)msg.wParam;
}  

LRESULT GameWindow::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	if (msg==WM_CLOSE)
	{
		PostQuitMessage(0);
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

bool GameWindow::InitWindow()
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = gamehInst;
	wc.hCursor = LoadCursor(gamehInst,(LPCWSTR)IDC_CURSOR1);
	wc.hIcon = LoadIcon(gamehInst,(LPCWSTR)IDI_ICON2);
	wc.hIconSm = LoadIcon(gamehInst, (LPCWSTR)IDI_ICON2);
	wc.hbrBackground = nullptr;
	wc.lpszClassName = gameClassName;
	RegisterClassEx(&wc);

	gamehWnd = CreateWindowEx(0, gameClassName, L"Happy Hard Window", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, 200, 200, 640, 480, nullptr, nullptr, gamehInst, nullptr);
	ShowWindow(gamehWnd, SW_SHOW);

	return true;
}

bool GameWindow::InitDirectX()
{
	DXGI_SWAP_CHAIN_DESC sd = { 0 };
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = gamehWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;
	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwap,
		&pDevice,
		nullptr,
		&pContext
	);

	ID3D11Resource* pBackBuffer = nullptr;
	pSwap->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer));
	pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pTarget);
	pBackBuffer->Release();

	return true;
}

bool GameWindow::InitImgui()
{
	ImGui::CreateContext();
	if (!ImGui_ImplWin32_Init(gamehWnd))
	{
		return false;
	}
	if (!ImGui_ImplDX11_Init(pDevice,pContext))
	{
		return false;
	}
	return true;
}

bool GameWindow::InitWorld()
{
	LoadModel* model = new LoadModel("ºúÌÒ.b");
	Buffer* buffer = new Buffer(pDevice, pContext);
	buffer->BindModelData(model);
	Shader* s = new Shader(L"VertexShader.cso", L"PixelShader.cso", pDevice);
	s->SetAllShader(pContext);
	InputLayout input(pDevice,pContext,s);
	pContext->OMSetRenderTargets(1u, &pTarget, nullptr);
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_VIEWPORT vp;
	vp.Width = 640;
	vp.Height = 480;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pContext->RSSetViewports(1u, &vp);
	return true;
}


void GameWindow::setFPS()
{
	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	// Compute averages over one second period.
	if ((mTimer.TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		std::wostringstream outs;
		outs.precision(4);
		outs << L"FPS: " << fps << L"    "
			<< L"Frame Time: " << mspf << L" (ms)";
		SetWindowText(gamehWnd, outs.str().c_str());

		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}
bool b = true;
void GameWindow::RenderScene()
{
	pContext->DrawIndexed(999999, 0, 0);
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::ShowDemoWindow(&b);
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void GameWindow::EndRender()
{
	pSwap->Present(1u, 0u);
}

void GameWindow::ClearScene(float red, float green, float blue)
{
	const float color[] = { red,green,blue,1.0f };
	pContext->ClearRenderTargetView(pTarget, color);
}
