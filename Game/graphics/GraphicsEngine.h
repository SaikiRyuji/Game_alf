#pragma once
#include"../Engine.h"
#include"../Camera/Camera.h"
#include"PostEffect\PostEffect.h"
#include"../EngineStruct.h"
/*!
 *@brief	グラフィックスエンジン。
 */
 /// <summary>
 /// レンダリングモード。
 /// </summary>
enum EnRenderMode {
	enRenderMode_Invalid,			//不正なレンダリングモード。
	enRenderSilhouette,				//シルエットレンダリング
	enRenderMode_CreateShadowMap,	//シャドウマップ生成。
	enRenderMode_Normal,			//通常レンダリング。
	enRenderMode_Num,				//レンダリングモードの数。
};
class GraphicsEngine 
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	/*!
	 *@brief	初期化。
	 *@param[in]	hWnd		ウィンドウハンドル。
	 */
	void Init(HWND hWnd);
	/*!
	 *@brief	解放。
	 */
	void Release();
	/*!
	 *@brief	D3D11デバイスを取得。
	 */
	ID3D11Device* GetD3DDevice()
	{
		return m_pd3dDevice;
	}
	/*!
	 *@brief	D3D11デバイスコンテキストを取得。
	 */
	/*ID3D11DeviceContext* GetD3DDeviceContext()
	{
		return m_pd3dDeviceContext;
	}*/

	/*!
	*@brief		フレームバッファの幅を取得。
	*/
	int GetFrameBufferWidth() const
	{
		return m_frameBufferWidth;
	}
	/*!
	*@brief		フレームバッファの高さを取得。
	*/
	int GetFrameBufferHeight() const
	{
		return m_frameBufferHeight;
	}
	/*!
	*@brief	メインカメラを取得。
	*/
	CCamera& GetMainCamera()
	{
		return m_mainCamera;
	}


	/*!
	*@brief	2Dカメラを取得。
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
	*@brief	ID3D11DeviceContextの取得。
	*/
	ID3D11DeviceContext* GetD3DDeviceContext() const
	{
		return m_pd3dDeviceContext;
	}
	
	/*!
	 *@brief	描画開始。
	 */
	void BegineRender();
	/*!
	 *@brief	描画終了。
	 */
	void EndRender();
	

private:
	D3D_FEATURE_LEVEL		m_featureLevel= D3D_FEATURE_LEVEL_11_0;				//Direct3D デバイスのターゲットとなる機能セット。
	ID3D11Device*			m_pd3dDevice = NULL;		//D3D11デバイス。
	IDXGISwapChain*			m_pSwapChain = NULL;		//スワップチェイン。
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;	//D3D11デバイスコンテキスト。
	ID3D11RenderTargetView* m_backBuffer = NULL;		//バックバッファ。
	ID3D11RasterizerState*	m_rasterizerState = NULL;	//ラスタライザステート。
	ID3D11Texture2D*		m_depthStencil = NULL;		//デプスステンシル。
	ID3D11DepthStencilView* m_depthStencilView = NULL;	//デプスステンシルビュー。
	CCamera m_mainCamera;
	CCamera					m_2dCamera;			//!<2Dカメラ。

	D3D_DRIVER_TYPE			m_driverType = D3D_DRIVER_TYPE_NULL;		//!<ドライバの種類のオプション。
	int						m_frameBufferWidth = 0;						//!<フレームバッファの幅。これが内部解像度。
	int						m_frameBufferHeight = 0;
	int						m_2dSpaceScreenWidth = 1280;				//!<2D空間のスクリーンの幅。2Dはこの座標系を前提に表示されていれば、解像度が変わっても大丈夫。
	int						m_2dSpaceScreenHeight = 720;
};

//extern CGraphicsEngine* g_graphicsEngine;			//グラフィックスエンジン