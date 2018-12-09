#pragma once
#include"../Engine.h"
#include"../Camera/Camera.h"
#include"PostEffect\PostEffect.h"
#include"../EngineStruct.h"
/*!
 *@brief	�O���t�B�b�N�X�G���W���B
 */
 /// <summary>
 /// �����_�����O���[�h�B
 /// </summary>
enum EnRenderMode {
	enRenderMode_Invalid,			//�s���ȃ����_�����O���[�h�B
	enRenderSilhouette,				//�V���G�b�g�����_�����O
	enRenderMode_CreateShadowMap,	//�V���h�E�}�b�v�����B
	enRenderMode_Normal,			//�ʏ탌���_�����O�B
	enRenderMode_Num,				//�����_�����O���[�h�̐��B
};
class GraphicsEngine 
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	/*!
	 *@brief	�������B
	 *@param[in]	hWnd		�E�B���h�E�n���h���B
	 */
	void Init(HWND hWnd);
	/*!
	 *@brief	����B
	 */
	void Release();
	/*!
	 *@brief	D3D11�f�o�C�X���擾�B
	 */
	ID3D11Device* GetD3DDevice()
	{
		return m_pd3dDevice;
	}
	/*!
	 *@brief	D3D11�f�o�C�X�R���e�L�X�g���擾�B
	 */
	/*ID3D11DeviceContext* GetD3DDeviceContext()
	{
		return m_pd3dDeviceContext;
	}*/

	/*!
	*@brief		�t���[���o�b�t�@�̕����擾�B
	*/
	int GetFrameBufferWidth() const
	{
		return m_frameBufferWidth;
	}
	/*!
	*@brief		�t���[���o�b�t�@�̍������擾�B
	*/
	int GetFrameBufferHeight() const
	{
		return m_frameBufferHeight;
	}
	/*!
	*@brief	���C���J�������擾�B
	*/
	CCamera& GetMainCamera()
	{
		return m_mainCamera;
	}


	/*!
	*@brief	2D�J�������擾�B
	*/
	CCamera& Get2DCamera()
	{
		return m_2dCamera;
	}

	ID3D11RenderTargetView* GetBackBuffer(){
		return m_backBuffer;
	}
	/*5
	/*!
	*@brief	ID3D11DeviceContext�̎擾�B
	*/
	ID3D11DeviceContext* GetD3DDeviceContext() const
	{
		return m_pd3dDeviceContext;
	}
	
	/*!
	 *@brief	�`��J�n�B
	 */
	void BegineRender();
	/*!
	 *@brief	�`��I���B
	 */
	void EndRender();
	

private:
	D3D_FEATURE_LEVEL		m_featureLevel= D3D_FEATURE_LEVEL_11_0;				//Direct3D �f�o�C�X�̃^�[�Q�b�g�ƂȂ�@�\�Z�b�g�B
	ID3D11Device*			m_pd3dDevice = NULL;		//D3D11�f�o�C�X�B
	IDXGISwapChain*			m_pSwapChain = NULL;		//�X���b�v�`�F�C���B
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;	//D3D11�f�o�C�X�R���e�L�X�g�B
	ID3D11RenderTargetView* m_backBuffer = NULL;		//�o�b�N�o�b�t�@�B
	ID3D11RasterizerState*	m_rasterizerState = NULL;	//���X�^���C�U�X�e�[�g�B
	ID3D11Texture2D*		m_depthStencil = NULL;		//�f�v�X�X�e���V���B
	ID3D11DepthStencilView* m_depthStencilView = NULL;	//�f�v�X�X�e���V���r���[�B
	CCamera m_mainCamera;
	CCamera					m_2dCamera;			//!<2D�J�����B

	D3D_DRIVER_TYPE			m_driverType = D3D_DRIVER_TYPE_NULL;		//!<�h���C�o�̎�ނ̃I�v�V�����B
	int						m_frameBufferWidth = 0;						//!<�t���[���o�b�t�@�̕��B���ꂪ�����𑜓x�B
	int						m_frameBufferHeight = 0;
	int						m_2dSpaceScreenWidth = 1280;				//!<2D��Ԃ̃X�N���[���̕��B2D�͂��̍��W�n��O��ɕ\������Ă���΁A�𑜓x���ς���Ă����v�B
	int						m_2dSpaceScreenHeight = 720;
};

//extern CGraphicsEngine* g_graphicsEngine;			//�O���t�B�b�N�X�G���W��