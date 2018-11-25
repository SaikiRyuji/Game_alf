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
	*@brief	�E�B���h�E�������B
	*/
	bool InitWindow(const SInitParam& initParam);
	/*!
	* @brief	�E�B���h�E�v���V�[�W���B
	*/
	static LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	bool Init(SInitParam& initParam);
	/*!
	*@brief	�Q�[�����[�v�����s�B
	*/
	void GameLoop();
	/*!
	* @brief	�X�V�B
	*/
	void Update();
	/*!
	*@brief	�C���X�^���X���擾�B
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
	*@brief	�������[���h�̎擾�B
	*/
	CPhysicsWorld& GetPhysicsWorld()
	{
		return m_physicsWorld;
	}
	/*!
	* @brief	�O���t�B�b�N�X�G���W���̎擾�B
	*/
	GraphicsEngine& GetGraphicsEngine()
	{
		return m_graphicsEngine;
	}
	HWND					m_hWnd = nullptr;	//!<�E�B���h�E�n���h���B
	GraphicsEngine			m_graphicsEngine;							//!<�O���t�B�b�N�G���W���B
	CPhysicsWorld			m_physicsWorld;								//!<�������[���h�B
	int						m_screenWidth = 0;							//!<�X�N���[���̕��B
	int						m_screenHeight = 0;							//!<�X�N���[���̍����B
	ID3D11DepthStencilState* m_depthStencilState;
};
/*!
* @brief	Engine�̃C���X�^���X���擾�B
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
* @brief	���C���J�����̃C���X�^���X���擾�B
*/
static inline CCamera& MainCamera()
{
	return GfxEngine().GetMainCamera();
}
/*!
* @brief	���C���J����(2D)�̃C���X�^���X���擾�B
*/
static inline CCamera& MainCamera2D()
{
	return GfxEngine().Get2DCamera();
}
/*!
* @brief	GPU�C�x���g�̊J�n�B
*/
static inline void BeginGPUEvent(const wchar_t* name)
{
}
/*!
* @brief	GPU�C�x���g�̏I���B
*/
static inline void EndGPUEvent()
{
}