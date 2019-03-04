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
	CMatrix m_rot = CMatrix::Identity();				//回転行列
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_CamPos = CVector3::Zero();				//カメラ座標
	CVector3 m_CamPosLen = CVector3::Zero();			//カメラ座標長さ
	CSpringCamera m_springCamera;						//バネカメラ
	CVector3 m_toCameraPos = CVector3::Zero();			//
	Player* m_player = nullptr;							//プレイヤーポインタ
	Player2D*m_pl2D = nullptr;							//2Dプレイヤーポインタ
	BackGround*m_background = nullptr;
	GameCamera2D*m_camera2D = nullptr;
};
