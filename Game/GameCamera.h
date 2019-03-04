#pragma once
#include"Camera\SpringCamera.h"
class Player;
class Player2D;
class BackGround;
class GameCamera2D;
class CGameCamera :public GameObject
{
public:
	CGameCamera();
	~CGameCamera();
	bool Start()override;
	void Update()override;
	void Camera2Dto3D(CVector3 pos);
	CSpringCamera& GetSpringCamera() {
		return m_springCamera;
	}
	CVector3 GetPosition() {
		return m_position;
	}
	void SetAvoidRot();
	void Notify2DGame();
	void NotifyGameOver();
	void NotifyGameClear();
	void Notify3DGame();
private:
	CMatrix m_rot = CMatrix::Identity();				//��]�s��
	CVector3 m_position = CVector3::Zero();				//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_CamPos = CVector3::Zero();				//�J�������W
	CVector3 m_CamPosLen = CVector3::Zero();			//�J�������W����
	CSpringCamera m_springCamera;						//�o�l�J����
	CVector3 m_toCameraPos = CVector3::Zero();			//
	Player* m_player = nullptr;							//�v���C���[�|�C���^
	Player2D*m_pl2D = nullptr;							//2D�v���C���[�|�C���^
	BackGround*m_background = nullptr;
	GameCamera2D*m_camera2D = nullptr;
};
