#include "stdafx.h"
#include "GameCamera2D.h"
#include"Player2D.h"
#include"BackGround.h"
#include"GameCamera.h"

GameCamera2D::GameCamera2D()
{
}


GameCamera2D::~GameCamera2D()
{
}

bool GameCamera2D::Start() {
	m_pl2D = FindGO<Player2D>("Player2D");
	m_background = FindGO<BackGround>("background");
	m_gamecamera = FindGO<CGameCamera>("Camera");
	MainCamera().SetTarget(m_pl2D->GetPosition());
	//ばねカメラの初期化。
	m_springCamera.Init(
		MainCamera(),		//ばねカメラの処理を行うカメラを指定する。
		500.0f,			//カメラの移動速度の最大値。
		false,				//カメラと地形とのあたり判定を取るかどうかのフラグ。trueだとあたり判定を行う。
		1.0f				//カメラに設定される球体コリジョンの半径。第３引数がtrueの時に有効になる。
	);
	m_springCamera.Update();
	CVector3 toCameraPos = CVector3::Zero();
	toCameraPos = m_springCamera.GetPosition() - m_springCamera.GetTarget();
	toCameraPos.y = 0.0f;
	float toCameraPosLen = toCameraPos.Length();

	CVector3 Pl2DPos = m_pl2D->GetPosition();
	CVector3 target = Pl2DPos;
	CVector3 ZInGhost = m_background->GetZInGhost();
	ZInGhost *= -1.0;
	ZInGhost.x *= toCameraPosLen;
	ZInGhost.z *= toCameraPosLen;
	CVector3 pos = target + ZInGhost;
	m_springCamera.SetTarget(target);
	m_springCamera.SetPosition(pos);
	return true;
}

void GameCamera2D::Update() {
	//カメラを更新。
	//注視点を計算する
	CVector3 Pl2DPos = m_pl2D->GetPosition();
	CVector3 target = Pl2DPos;
	//プレイヤの足元からちょっと上を注視点とする。
	target.y += 10.0f;
	//視点を計算する。
	CVector3 toPos = (m_background->GetZInGhost())*-1.0f*50.0f;
	CVector3 pos = target + toPos;	//キャラクタを斜め上から見ているような視点にする。
									//メインカメラに注視点と視点を設定する
	m_springCamera.SetTarget(target);
	m_springCamera.SetPosition(pos);
	float x = g_pad->GetRStickXF();
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), 2.0f*x);
	qRot.Multiply(toPos);
	//視点を計算する
	if (!(x == 0)) {
		pos = target + toPos;
		m_springCamera.SetTarget(target);
		m_springCamera.SetPosition(pos);
	}
	m_position = pos;
	m_springCamera.Update();
}
void GameCamera2D::Notify3DGame() {
	//バネカメラをリフレッシュ。
	m_springCamera.Refresh();
	m_gamecamera->Notify3DGame();
	m_gamecamera->Camera2Dto3D(m_position);
	
	//バネカメラを非アクティブにする。
	m_isActive = false;
	
}
void GameCamera2D::NotifyGameOver() {
	//バネカメラをリフレッシュ。
	m_springCamera.Refresh();
	//バネカメラを非アクティブにする。
	m_isActive = false;
}
void GameCamera2D::NotifyGameClear() {
	//バネカメラをリフレッシュ。
	m_springCamera.Refresh();
	//バネカメラを非アクティブにする。
	m_isActive = false;
}
void GameCamera2D::Notify2DGame() {
	//バネカメラをリフレッシュ。
	m_springCamera.Refresh();
	//バネカメラをアクティブにする。
	m_isActive = true;
}