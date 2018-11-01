#pragma once
class CCamera
{
public:
	enum EnUpdateProjMatrixFunc {
		enUpdateProjMatrixFunc_Perspective,		//!<�����ˉe�s��B���ߖ@���������G����肽���Ȃ炱�����B
		enUpdateProjMatrixFunc_Ortho,			//!<���s���e�B�Q�c�I�ȕ\�����������Ȃ炱�����B
	};
	/*!
	 * @brief	�J�����s��A�v���W�F�N�V�����s��̍X�V�B
	 *@details
	 * ���ݐݒ肳��Ă���A�����_�A���_�A��p�Ȃǂ̏������Ƃ�
	 * �J�����s��ƃv���W�F�N�V�����s����X�V���܂��B
	 * ���̊֐����Ă΂Ȃ��ƁA�J�����͓����Ȃ��̂Œ��ӂ��K�v�ł��B
	 */
	void Update();
	/*!
	 * @brief	�J�����s����擾�B
	 */
	CMatrix GetViewMatrix()
	{
		return m_viewMatrix;
	}
	/*!
	 * @brief	�v���W�F�N�V�����s����擾�B
	 */
	CMatrix GetProjectionMatrix() 
	{
		return m_projMatrix;
	}
	/*!
	 * @brief	���_���擾�B
	 */
	CVector3 GetPosition()
	{
		return m_position;
	}
	/*!
	 * @brief	�����_���擾�B
	 */
	CVector3 GetTarget()
	{
		return m_target;
	}
	/*!
	 * @brief	�J�����̏�������擾�B
	 */
	CVector3 GetUp()
	{
		return m_up;
	}
	/*!
	* @brief	�J�����̑O���������擾�B
	*/
	const CVector3& GetForward() const
	{
		return m_forward;
	}
	/*!
	* @brief	�J�����̉E�������擾�B
	*/
	const CVector3& GetRight() const
	{
		return m_right;
	}
	/*!
	* @brief	�J�����̉�]�s����擾�B
	*/
	const CMatrix& GetCameraRotation() const
	{
		return m_cameraRotation;
	}
	float GetViewAngle() {
		return m_viewAngle;
	}
	/*!
	 * @brief	���_��ݒ�B
	 */
	void SetPosition( CVector3 pos )
	{
		m_position = pos;
	}
	/*!
	* @brief	���s���e�̍�����ݒ�B
	*@details
	* m_updateProjMatrixFunc��enUpdateProjMatrixFunc_Ortho�̎��Ɏg�p�����B
	*/
	void SetUpdateProjMatrixFunc(EnUpdateProjMatrixFunc func)
	{
		m_updateProjMatrixFunc = func;
	}
	/*!
	 * @brief	�����_��ݒ�B
	 */
	void SetTarget( CVector3 target )
	{
		m_target = target;
	}
	/*!
	 * @brief	�J�����̏������ݒ�B
	 */
	void SetUp( CVector3 up )
	{
		m_up = up;
	}
	/*!
	 * @brief	�����ʂ�ݒ�B
	 */
	void SetFar( float f )
	{
		m_far = f;
	}
	/*!
	 * @brief	�ߕ��ʂ�ݒ�B
	 */
	void SetNear( float n )
	{
		m_near = n;
	}
	/*!
	 * @brief	��p��ݒ�B
	 */
	void SetViewAngle( float angle )
	{
		m_viewAngle = angle;
	}
private:
	CMatrix	m_viewMatrix = CMatrix::Identity();		//�r���[�s��B
	CMatrix m_projMatrix = CMatrix::Identity();		//�v���W�F�N�V�����s��B
	CMatrix		m_viewMatrixInv;					//!<�r���[�s��̋t�s��B
	CMatrix		m_cameraRotation;					//!<�J�����̉�]�s��B
	CVector3 m_target = CVector3::Zero();			//�����_�B
	CVector3 m_position = CVector3::Zero();			//���_�B
	CVector3 m_up = CVector3::Up();					//������B
	float m_viewAngle = CMath::DegToRad(60.0f);		//��p�B
	CVector3	m_forward = CVector3::Front();		//!<�J�����̑O���B
	CVector3	m_right = CVector3::Right();			//!<�J�����̉E�B
	float m_far = 10000.0f;							//�������ʂ܂ł̋����B
	float m_near = 1.0f;							//�ߕ��ʂ܂ł̋����B
	EnUpdateProjMatrixFunc m_updateProjMatrixFunc = enUpdateProjMatrixFunc_Perspective;	//!<�v���W�F�N�V�����s��̍X�V�̎d���B
};

//extern CCamera g_camera3D;		//!<3D�J�����B