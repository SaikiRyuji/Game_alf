#include "stdafx.h"
#include "GameCamera.h"


CGameCamera::CGameCamera()
{
}


CGameCamera::~CGameCamera()
{
}

bool CGameCamera::Start()
{
	m_player = FindGO<Player>("Player");
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
		true,				//カメラと地形とのあたり判定を取るかどうかのフラグ。trueだとあたり判定を行う。
		1.0f				//カメラに設定される球体コリジョンの半径。第３引数がtrueの時に有効になる。
	);
	return true;
}
void CGameCamera::SetAvoidRot() {

}
void CGameCamera::Update() {

	CVector3 toCameraPos = CVector3::Zero();
	toCameraPos = m_springCamera.GetPosition() - m_springCamera.GetTarget();
	float height = toCameraPos.y;
	toCameraPos.y = 0.0f;
	float toCameraPosLen = toCameraPos.Length();
	toCameraPos.Normalize();
	CVector3 target = m_player->GetPosition();
	target.y += 10.0f;
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

	m_rot.MakeRotationFromQuaternion(qRot);

	//視点を計算する
	if (!(x == 0 && y == 0)) {
		pos = target + toNewCameraPos;
		m_springCamera.SetTarget(target);
		m_springCamera.SetPosition(pos);
	}
	//照準
	if (g_pad->IsPress(enButtonLB2)) {
	/*	CVector3 vec;
		vec = MainCamera().GetForward()*20.0f;
		target += vec;*/
		target = m_player->GetTarPosition();
		pos = target + toNewCameraPos;
		m_springCamera.SetTarget(target);
		m_springCamera.SetPosition(pos);
	}
	//バネカメラの更新。
	m_springCamera.Update();
}