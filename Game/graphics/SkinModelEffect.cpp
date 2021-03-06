#include "stdafx.h"
#include "graphics/SkinModelEffect.h"
#include "graphics/SkinModelShaderConst.h"


ModelEffect::ModelEffect()
{
	//頂点シェーダーをロード。
	m_vsShader.Load("Assets/shader/model.fx", "VSMain", Shader::EnType::VS);
	m_psShader.Load("Assets/shader/model.fx", "PSMain", Shader::EnType::PS);
	m_psSilhouette.Load("Assets/shader/model.fx", "PSMain_Silhouette", Shader::EnType::PS);

	//デプスステンシルの初期化。
	InitSilhouettoDepthStepsilState();

}

ModelEffect::~ModelEffect()
{
	//if (m_albedoTexture != nullptr) {
	//	m_albedoTexture->Release();
	//}
	//if (m_silhouettoDepthStepsilState != nullptr) {
	//	m_silhouettoDepthStepsilState->Release();
	//}
}

void ModelEffect::InitSilhouettoDepthStepsilState()
{
	//D3Dデバイスを取得。
	auto pd3d = GfxEngine().GetD3DDevice();
	//作成する深度ステンシルステートの定義を設定していく。
	D3D11_DEPTH_STENCIL_DESC desc = { 0 };
	desc.DepthEnable = true;						   //Zテストが有効。
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; //ZバッファにZ値を描き込まない。
	desc.DepthFunc = D3D11_COMPARISON_GREATER;		   //Z値が大きければフレームバッファに描き込む。

	pd3d->CreateDepthStencilState(&desc, &m_silhouettoDepthStepsilState);
}
void __cdecl ModelEffect::Apply(ID3D11DeviceContext* deviceContext)
{
	deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShader.GetBody(), NULL, 0);
	switch (m_renderMode) {
	case enRenderMode_Normal:
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShader.GetBody(), NULL, 0);
		deviceContext->PSSetShaderResources(enSkinModelSRVReg_AlbedoTexture, 1, &m_albedoTex);
		break;
	case enRenderSilhouette:
		//シルエット描画。
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psSilhouette.GetBody(), NULL, 0);
		//デプスステンシルステートを切り替える。
		deviceContext->OMSetDepthStencilState(m_silhouettoDepthStepsilState, 0);
		break;
	}
}