#pragma once
#include"Camera\SpringCamera.h"
class Player2D;
class BackGround;
class CGameCamera;
class GameCamera2D:public GameObject
{
public:
	GameCamera2D();
	~GameCamera2D();
	bool Start()override;
	void Update()override;
	void Notify2DGame();
	void Notify3DGame();
	void NotifyGameOver();
	void NotifyGameClear();
private:
	CMatrix m_rot = CMatrix::Identity();				//��]�s��
	CVector3 m_position = CVector3::Zero();				//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CVector3 m_CamPos = CVector3::Zero();				//�J�������W
	CVector3 m_CamPosLen = CVector3::Zero();			//�J�������W����
	CSpringCamera m_springCamera;						//�o�l�J����
	CVector3 m_toCameraPos = CVector3::Zero();			//
	Player2D*m_pl2D = nullptr;							//2D�v���C���[�|�C���^
	BackGround*m_background = nullptr;
	CGameCamera*m_gamecamera = nullptr;
};

