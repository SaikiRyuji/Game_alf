#pragma once
#include"Camera\SpringCamera.h"
#include"Player.h"
class CGameCamera :public GameObject
{
public:
	CGameCamera();
	~CGameCamera();
	bool Start();
	void Update();
	CSpringCamera& GetSpringCamera() {
		return m_springCamera;
	}
	CVector3 GetPosition() {
		return m_position;
	}
	void SetAvoidRot();
private:
	CMatrix m_rot = CMatrix::Identity();				//��]�s��
	CVector3 m_position = CVector3::Zero();				//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_CamPos = CVector3::Zero();				//�J�������W
	CVector3 m_CamPosLen = CVector3::Zero();			//�J�������W����
	CSpringCamera m_springCamera;						//�o�l�J����
	CVector3 m_toCameraPos = CVector3::Zero();			//
	Player* m_player = nullptr;							//�v���C���[�|�C���^
};
