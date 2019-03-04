#pragma once
#include "RenderTarget.h"

class SkinModel;

class ShadowMap
{
public:
	ShadowMap();
	~ShadowMap();

	/// <summary>
	/// ライトビュー行列を取得。
	/// </summary>
	/// <returns></returns>
	CMatrix GetLighViewMatrix() const
	{
		return m_lightViewMatrix;
	}

	/// <summary>
	/// ライトプロジェクション行列を取得。
	/// </summary>
	/// <returns></returns>
	CMatrix GetLightProjMatrix() const
	{
		return m_lightProjMatrix;
	}

	// 更新
	//ライトカメラの視点の座標
	//ライトかめらの注視点の座標
	void UpdateFromLightTarget(CVector3 lightCameraPos, CVector3 lightCameraTarget);

	/// <summary>
	/// 更新(ライトカメラの向きを指定するバージョン。
	/// </summary>
	/// <remarks>
	/// ライトビュー行列や、ライトプロジェクション行列を
	/// 更新します。UpdateFromLightTargetかUpdateFromLightDirectionのどちらかを
	/// 毎フレーム呼び出してください。
	/// </remarks>
	/// <param name="lightCameraPos">ライトカメラの視点の座標</param>
	/// <param name="lightDir">ライトの方向</param>
	void UpdateFromLightDirection(CVector3 lightCameraPos, CVector3 lightDir);

	/// <summary>
	/// シャドウマップにシャドウキャスターをレンダリング。
	/// 毎フレーム呼び出して下さい。
	/// </summary>
	/// <remarks>
	/// シャドウマップに描画されるシャドウキャスターは
	/// RegistShadowCaster関数を使用して登録されたキャスターのみです。
	/// この関数を呼び出すと、シャドウキャスターのリストはクリアされます。
	/// </remarks>
	void RenderToShadowMap();

	/// <summary>
	/// シャドウキャスターを登録。
	/// </summary>
	/// <remarks>
	/// この関数を使って、登録されたキャスターが
	/// シャドウマップに描画されます。
	/// 登録されたキャスターのリストはRenderToShadowMapを呼び出したら
	/// クリアされるため、常に影を生成したい場合は、
	/// 毎フレームこの関数を呼び出す必要があります。
	/// </remarks>
	/// <param name="shadowCaster">シャドウキャスター</param>
	void RegistShadowCaster(SkinModel* shadowCaster)
	{
		m_shadowCasters.push_back(shadowCaster);
	}

	/// <summary>
	/// シャドウマップのSRVを取得。
	/// </summary>
	/// <returns>シャドウマップのSRV</returns>
	ID3D11ShaderResourceView* GetShadowMapSRV()
	{
		return m_shadowMapRT.GetRenderTargetSRV();
	}
private:
	CVector3 m_lightCameraPosition = CVector3::Zero();	//ライトカメラの視点。
	CVector3 m_lightCameraTarget = CVector3::Zero();	//ライトカメラの注視点。
	CMatrix m_lightViewMatrix = CMatrix::Identity();	//ライトビュー行列。
	CMatrix m_lightProjMatrix = CMatrix::Identity();	//ライトプロジェクション行列。
	RenderTarget m_shadowMapRT;						//シャドウマップを描画するレンダリングターゲット。
	std::vector< SkinModel*> m_shadowCasters;	//シャドウキャスターの配列。
};

