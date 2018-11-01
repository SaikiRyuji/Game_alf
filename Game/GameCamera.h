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
	CMatrix m_rot = CMatrix::Identity();				//回転行列
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_CamPos = CVector3::Zero();				//カメラ座標
	CVector3 m_CamPosLen = CVector3::Zero();			//カメラ座標長さ
	CSpringCamera m_springCamera;						//バネカメラ
	CVector3 m_toCameraPos = CVector3::Zero();			//
	Player* m_player = nullptr;							//プレイヤーポインタ
};
