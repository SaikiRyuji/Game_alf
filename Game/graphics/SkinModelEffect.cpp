#include "stdafx.h"
#include "graphics/SkinModelEffect.h"
#include "graphics/SkinModelShaderConst.h"


ModelEffect::ModelEffect()
{
	//���_�V�F�[�_�[�����[�h�B
	m_vsShader.Load("Assets/shader/model.fx", "VSMain", Shader::EnType::VS);
	m_psShader.Load("Assets/shader/model.fx", "PSMain", Shader::EnType::PS);
	m_psSilhouette.Load("Assets/shader/model.fx", "PSMain_Silhouette", Shader::EnType::PS);

	//�f�v�X�X�e���V���̏������B
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
	//D3D�f�o�C�X���擾�B
	auto pd3d = GfxEngine().GetD3DDevice();
	//�쐬����[�x�X�e���V���X�e�[�g�̒�`��ݒ肵�Ă����B
	D3D11_DEPTH_STENCIL_DESC desc = { 0 };
	desc.DepthEnable = true;						   //Z�e�X�g���L���B
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; //Z�o�b�t�@��Z�l��`�����܂Ȃ��B
	desc.DepthFunc = D3D11_COMPARISON_GREATER;		   //Z�l���傫����΃t���[���o�b�t�@�ɕ`�����ށB

	pd3d->CreateDepthStencilState(&desc, &m_silhouettoDepthStepsilState);
}
void __cdecl ModelEffect::Apply(ID3D11DeviceContext* deviceContext)
{
	deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShader.GetBody(), NULL, 0);
	switch (m_renderMode) {
	case 0:
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShader.GetBody(), NULL, 0);
		deviceContext->PSSetShaderResources(enSkinModelSRVReg_AlbedoTexture, 1, &m_albedoTex);
		break;
	case 1:
		//�V���G�b�g�`��B
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psSilhouette.GetBody(), NULL, 0);
		//�f�v�X�X�e���V���X�e�[�g��؂�ւ���B
		deviceContext->OMSetDepthStencilState(m_silhouettoDepthStepsilState, 0);
		break;
	}
}