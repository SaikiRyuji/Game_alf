#pragma once
#include"graphics\Primitive.h"
/*!
*@brief	ポストエフェクト。
*/
class CPostEffect : Noncopyable {
public:
	/*!
	*@brief	コンストラクタ。
	*/
	CPostEffect();
	/*!
	*@brief	デストラクタ。
	*/
	~CPostEffect();
	/*!
	*@brief	開放。
	*/
	void Release();
	/*!
	*@brief	作成。
	*@param[in]	config		コンフィグ。
	*/
	void Create();
	/*!
	*@brief	描画。
	*@param[in]		rc		レンダリングコンテキスト。
	*/
	void Draw();
	/*!
	*@brief	フルスクリーン描画。
	*@param[in]		rc		レンダリングコンテキスト。
	*/
	void DrawFullScreenQuad();
	/*!
	* @brief	最終書き込みのレンダリングターゲットを切り替え。
	*/
	void ToggleFinalRenderTarget()
	{
		m_currentFinalRenderTarget ^= 1;
	}
	/*!
	* @brief	最終書き込みのレンダリングターゲットの取得。
	*/
	/*CRenderTarget& GetFinalRenderTarget()
	{
		return m_finalRenderTarget[m_currentFinalRenderTarget];
	}*/
private:
	/*!
	*@brief	フルスクリーン描画用の矩形プリミティブの初期化。。
	*/
	void InitFullScreenQuadPrimitive();
	/*!
	*@brief	ポストエフェクトの最終書き込み先となるレンダリングターゲット。
	*/
	void InitFinalRenderTarget();
private:
	//CFxaa		m_fxaa;						//!<FXAA。
	//CBloom		m_bloom;					//!<BLOOM。
	//CTonemap	m_tonemap;					//!<トーンマップ。
	//CDithering	m_dithering;				//!<ディザリング。
	CPrimitive	m_fullscreenQuad;			//!<フルスクリーン描画用の矩形プリミティブ。
	int	m_currentFinalRenderTarget = 0;				//!<現在のメインレンダリングターゲット。
	//CRenderTarget m_finalRenderTarget[2];	//!<ポストエフェクトの最終書き込み先となるレンダリングターゲット。

};

