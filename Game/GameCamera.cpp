#include "stdafx.h"
#include "GameCamera.h"
#include"Player.h"
#include"Player2D.h"
#include"BackGround.h"
#include"GameCamera2D.h"

CGameCamera::CGameCamera()
{
}


CGameCamera::~CGameCamera()
{
}

bool CGameCamera::Start()
{
	m_player = FindGO<Player>("Player");
	m_pl2D = FindGO<Player2D>("Player2D");
	m_background = FindGO<BackGround>("background");
	m_CamPos = m_player->GetPosition();
	m_CamPos.y += 20.0f;
	m_CamPos.z -= 50.0f;
	//カメラを初期化。
	MainCamera().SetPosition(m_CamPos);
	MainCamera().SetTarget(m_player->GetPosition());
	MainCamera().SetFar(10000.0f);
	m_CamPosLen = m_player->GetPosition() - m_CamPos;
	//ばねカメラの初期化。
	m_springCamera.Init(
		MainCamera(),		//ばねカメラの処理を行うカメラを指定する。
		500.0f,			//カメラの移動速度の最大値。
		false,				//カメラと地形とのあたり判定を取るかどうかのフラグ。trueだとあたり判定を行う。
		1.0f				//カメラに設定される球体コリジョンの半径。第３引数がtrueの時に有効になる。
	);
	return true;
}
void CGameCamera::Camera2Dto3D(CVector3 pos) {
	CVector3 plpos=CVector3::Zero();
	plpos = m_player->GetPosition();
	plpos.y += 20.0f;
	pos.y = plpos.y;
	m_springCamera.SetPosition(pos);
	m_springCamera.SetTarget(plpos);
	m_springCamera.Update();
}
void CGameCamera::SetAvoidRot() {

}
void CGameCamera::Update() {
	CVector3 PlPos = m_player->GetPosition();
	CVector3 toCameraPos = CVector3::Zero();
	toCameraPos = m_springCamera.GetPosition() - m_springCamera.GetTarget();
	float height = toCameraPos.y;
	toCameraPos.y = 0.0f;
	float toCameraPosLen = toCameraPos.Length();
	toCameraPos.Normalize();
	CVector3 target = PlPos;
	//target.y += 10.0f;
	CVector3 toNewCameraPos = CVector3::Zero();
	toNewCameraPos = m_springCamera.GetPosition() - target;
	toNewCameraPos.y = 0.0f;
	float toNewCameraPosLen = toNewCameraPos.Length();
	toNewCameraPos.Normalize();

	//ちょっとずつ追尾
	float weight = 0.8f;
	toNewCameraPos = toNewCameraPos * weight + toCameraPos * (1.0f - weight);
	toNewCameraPos.Normalize();
	toNewCameraPos.x *= toCameraPosLen;
	toNewCameraPos.y *= toCameraPosLen;
	toNewCameraPos.z *= toCameraPosLen;
	toNewCameraPos.y = height;
	CVector3 pos = target + toNewCameraPos;
	m_springCamera.SetTarget(target);
	m_springCamera.SetPosition(pos);
	CVector3 toCameraPosOld = toNewCameraPos;
	//パッドの入力を使ってカメラを回す
	float x = g_pad->GetRStickXF();
	float y = g_pad->GetRStickYF();
	//Y軸周りの回転
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), 2.0f*x);
	qRot.Multiply(toNewCameraPos);
	//x軸周りの回転
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY(), toNewCameraPos);
	axisX.Normalize();
	//任意の軸に回転させる
	qRot.SetRotationDeg(axisX, 2.0f*y);
	qRot.Multiply(toNewCameraPos);
	//カメラの回転の上限を設定
	CVector3 toPosDir = toNewCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		//カメラの上を制御
		toNewCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.8f) {
		//カメラの下を制御
		toNewCameraPos = toCameraPosOld;
	}
	pos = CVector3::Zero();

	//視点を計算する
	if (!(x == 0 && y == 0)) {
		pos = target + toNewCameraPos;
		m_springCamera.SetTarget(target);
		m_springCamera.SetPosition(pos);
	}
	//バネカメラの更新。
	m_springCamera.Update();
}
void CGameCamera::Notify2DGame() {
	m_camera2D = FindGO<GameCamera2D>("Camera2D");
	m_camera2D->Notify2DGame();
	m_camera2D->Start();
	//バネカメラをリフレッシュ。
	m_springCamera.Refresh();
	//バネカメラを非アクティブにする。
	m_isActive = false;
}
void CGameCamera::NotifyGameOver() {
	//バネカメラをリフレッシュ。
	m_springCamera.Refresh();
	//バネカメラを非アクティブにする。
	m_isActive = false;
}
void CGameCamera::NotifyGameClear() {
	//バネカメラをリフレッシュ。
	m_springCamera.Refresh();
	//バネカメラを非アクティブにする。
	m_isActive = false;
}
void CGameCamera::Notify3DGame() {
	//バネカメラをリフレッシュ。
	m_springCamera.Refresh();
	//バネカメラをアクティブにする。
	m_isActive = true;
}