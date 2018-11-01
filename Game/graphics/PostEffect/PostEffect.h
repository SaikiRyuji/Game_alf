#pragma once
#include"graphics\Primitive.h"
/*!
*@brief	�|�X�g�G�t�F�N�g�B
*/
class CPostEffect : Noncopyable {
public:
	/*!
	*@brief	�R���X�g���N�^�B
	*/
	CPostEffect();
	/*!
	*@brief	�f�X�g���N�^�B
	*/
	~CPostEffect();
	/*!
	*@brief	�J���B
	*/
	void Release();
	/*!
	*@brief	�쐬�B
	*@param[in]	config		�R���t�B�O�B
	*/
	void Create();
	/*!
	*@brief	�`��B
	*@param[in]		rc		�����_�����O�R���e�L�X�g�B
	*/
	void Draw();
	/*!
	*@brief	�t���X�N���[���`��B
	*@param[in]		rc		�����_�����O�R���e�L�X�g�B
	*/
	void DrawFullScreenQuad();
	/*!
	* @brief	�ŏI�������݂̃����_�����O�^�[�Q�b�g��؂�ւ��B
	*/
	void ToggleFinalRenderTarget()
	{
		m_currentFinalRenderTarget ^= 1;
	}
	/*!
	* @brief	�ŏI�������݂̃����_�����O�^�[�Q�b�g�̎擾�B
	*/
	/*CRenderTarget& GetFinalRenderTarget()
	{
		return m_finalRenderTarget[m_currentFinalRenderTarget];
	}*/
private:
	/*!
	*@brief	�t���X�N���[���`��p�̋�`�v���~�e�B�u�̏������B�B
	*/
	void InitFullScreenQuadPrimitive();
	/*!
	*@brief	�|�X�g�G�t�F�N�g�̍ŏI�������ݐ�ƂȂ郌���_�����O�^�[�Q�b�g�B
	*/
	void InitFinalRenderTarget();
private:
	//CFxaa		m_fxaa;						//!<FXAA�B
	//CBloom		m_bloom;					//!<BLOOM�B
	//CTonemap	m_tonemap;					//!<�g�[���}�b�v�B
	//CDithering	m_dithering;				//!<�f�B�U�����O�B
	CPrimitive	m_fullscreenQuad;			//!<�t���X�N���[���`��p�̋�`�v���~�e�B�u�B
	int	m_currentFinalRenderTarget = 0;				//!<���݂̃��C�������_�����O�^�[�Q�b�g�B
	//CRenderTarget m_finalRenderTarget[2];	//!<�|�X�g�G�t�F�N�g�̍ŏI�������ݐ�ƂȂ郌���_�����O�^�[�Q�b�g�B

};

