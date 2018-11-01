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
	//�E�B���h�E�������B
	if (!InitWindow(initParam)) {
		return false;
	}
	//GameObjectManager�̏������B
	GOM().Init(initParam.gameObjectPrioMax);
	m_graphicsEngine.Init(m_hWnd);
	//����������
	m_physicsWorld.Init();
	
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
			//�X�V�B
			Update();
		}
	}
}

void CEngine::Update() {
	//�`��J�n�B
	m_graphicsEngine.BegineRender();
	//�Q�[���p�b�h�̍X�V�B	
	for (auto& pad : g_pad) {
		pad.Update();
	}
	//�����G���W���̍X�V�B
	m_physicsWorld.Update();
	//GameObjectManager�X�V�B�`��B
	GOM().Execute();
	//�`��I���B
	m_graphicsEngine.EndRender();
}