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
	CMatrix m_rot = CMatrix::Identity();				//回転行列
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CVector3 m_CamPos = CVector3::Zero();				//カメラ座標
	CVector3 m_CamPosLen = CVector3::Zero();			//カメラ座標長さ
	CSpringCamera m_springCamera;						//バネカメラ
	CVector3 m_toCameraPos = CVector3::Zero();			//
	Player2D*m_pl2D = nullptr;							//2Dプレイヤーポインタ
	BackGround*m_background = nullptr;
	CGameCamera*m_gamecamera = nullptr;
};

