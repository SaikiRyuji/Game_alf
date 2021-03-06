#include "stdafx.h"
#include "Engine.h"
#include"Player.h"


CEngine::CEngine()
{
}


CEngine::~CEngine()
{
}
bool CEngine::InitWindow(const SInitParam& initParam) {
	m_screenHeight = initParam.screenHeight;
	m_screenWidth = initParam.screenWidth;
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		MsgProc, 
		0L,
		0L,
		GetModuleHandle(nullptr), 
		nullptr, 
		nullptr,
		nullptr, 
		nullptr,
		TEXT("GameDemo"), 
		nullptr
	};
	RegisterClassEx(&wc);
	// Create the application's window
	m_hWnd = CreateWindow(
		TEXT("GameDemo"),
		TEXT("GameDemo"),
		WS_OVERLAPPEDWINDOW, 
		0, 
		0, 
		m_screenWidth,
		m_screenHeight,
		nullptr, nullptr,
		wc.hInstance, 
		nullptr);

	ShowWindow(m_hWnd, initParam.nCmdShow);
	return m_hWnd != nullptr;
}
LRESULT CALLBACK CEngine::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (msg)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}
//extern HWND g_hWnd;
bool CEngine::Init(SInitParam& initParam)
{
	//ウィンドウ初期化。
	if (!InitWindow(initParam)) {
		return false;
	}
	//GameObjectManagerの初期化。
	GOM().Init(initParam.gameObjectPrioMax);
	m_graphicsEngine.Init(m_hWnd);
	//物理初期化
	m_physicsWorld.Init();

	//深度ステンシルステート作成
	D3D11_DEPTH_STENCIL_DESC desc = { 0 };
	desc.DepthEnable = true;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	desc.DepthFunc = D3D11_COMPARISON_GREATER;
	desc.StencilEnable = false;
	desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//D3Dデバイスを取得。
	auto d3ddevice = GfxEngine().GetD3DDevice();
	//デプスステンシルステートを作成。
	d3ddevice->CreateDepthStencilState(&desc, &m_depthStencilState);

	
	return true;
}

void CEngine::GameLoop()
{
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//更新。
			Update();
		}
	}
}

void CEngine::Update() {
	//描画開始。
	m_graphicsEngine.BegineRender();

	//なくてもできている？
	//m_graphicsEngine.GetD3DDeviceContext()->OMSetDepthStencilState(m_depthStencilState, 0);
	//ゲームパッドの更新。	
	for (auto& pad : g_pad) {
		pad.Update();
	}
	//物理エンジンの更新。
	m_physicsWorld.Update();
	//GameObjectManager更新。描画。
	GOM().Execute();
	//描画終了。
	m_graphicsEngine.EndRender();
}