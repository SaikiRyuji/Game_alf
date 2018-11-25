#pragma once
#include "physics/Physics.h"
#include"graphics\GraphicsEngine.h"
#include"EngineStruct.h"

class CEngine :Noncopyable
{
public:
	CEngine();
	~CEngine();
	/*!
	*@brief	ウィンドウ初期化。
	*/
	bool InitWindow(const SInitParam& initParam);
	/*!
	* @brief	ウィンドウプロシージャ。
	*/
	static LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	bool Init(SInitParam& initParam);
	/*!
	*@brief	ゲームループを実行。
	*/
	void GameLoop();
	/*!
	* @brief	更新。
	*/
	void Update();
	/*!
	*@brief	インスタンスを取得。
	*/
	static CEngine& GetInstance()
	{
		static CEngine* instance = nullptr;
		if (instance == nullptr) {
			instance = new CEngine;
		}
		return *instance;
	}
	/*!
	*@brief	物理ワールドの取得。
	*/
	CPhysicsWorld& GetPhysicsWorld()
	{
		return m_physicsWorld;
	}
	/*!
	* @brief	グラフィックスエンジンの取得。
	*/
	GraphicsEngine& GetGraphicsEngine()
	{
		return m_graphicsEngine;
	}
	HWND					m_hWnd = nullptr;	//!<ウィンドウハンドル。
	GraphicsEngine			m_graphicsEngine;							//!<グラフィックエンジン。
	CPhysicsWorld			m_physicsWorld;								//!<物理ワールド。
	int						m_screenWidth = 0;							//!<スクリーンの幅。
	int						m_screenHeight = 0;							//!<スクリーンの高さ。
	ID3D11DepthStencilState* m_depthStencilState;
};
/*!
* @brief	Engineのインスタンスを取得。
*/
static inline CEngine& Engine()
{
	return CEngine::GetInstance();
}
static inline CPhysicsWorld& PhysicsWorld()
{
	return Engine().GetPhysicsWorld();
}
static inline GraphicsEngine& GfxEngine()
{
	return Engine().GetGraphicsEngine();
}

/*!
* @brief	メインカメラのインスタンスを取得。
*/
static inline CCamera& MainCamera()
{
	return GfxEngine().GetMainCamera();
}
/*!
* @brief	メインカメラ(2D)のインスタンスを取得。
*/
static inline CCamera& MainCamera2D()
{
	return GfxEngine().Get2DCamera();
}
/*!
* @brief	GPUイベントの開始。
*/
static inline void BeginGPUEvent(const wchar_t* name)
{
}
/*!
* @brief	GPUイベントの終了。
*/
static inline void EndGPUEvent()
{
}