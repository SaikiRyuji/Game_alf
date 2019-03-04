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
	//�J�������������B
	MainCamera().SetPosition(m_CamPos);
	MainCamera().SetTarget(m_player->GetPosition());
	MainCamera().SetFar(10000.0f);
	m_CamPosLen = m_player->GetPosition() - m_CamPos;
	//�΂˃J�����̏������B
	m_springCamera.Init(
		MainCamera(),		//�΂˃J�����̏������s���J�������w�肷��B
		500.0f,			//�J�����̈ړ����x�̍ő�l�B
		false,				//�J�����ƒn�`�Ƃ̂����蔻�����邩�ǂ����̃t���O�Btrue���Ƃ����蔻����s���B
		1.0f				//�J�����ɐݒ肳��鋅�̃R���W�����̔��a�B��R������true�̎��ɗL���ɂȂ�B
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

	//������Ƃ��ǔ�
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
	//�p�b�h�̓��͂��g���ăJ��������
	float x = g_pad->GetRStickXF();
	float y = g_pad->GetRStickYF();
	//Y������̉�]
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), 2.0f*x);
	qRot.Multiply(toNewCameraPos);
	//x������̉�]
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY(), toNewCameraPos);
	axisX.Normalize();
	//�C�ӂ̎��ɉ�]������
	qRot.SetRotationDeg(axisX, 2.0f*y);
	qRot.Multiply(toNewCameraPos);
	//�J�����̉�]�̏����ݒ�
	CVector3 toPosDir = toNewCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		//�J�����̏�𐧌�
		toNewCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.8f) {
		//�J�����̉��𐧌�
		toNewCameraPos = toCameraPosOld;
	}
	pos = CVector3::Zero();

	//���_���v�Z����
	if (!(x == 0 && y == 0)) {
		pos = target + toNewCameraPos;
		m_springCamera.SetTarget(target);
		m_springCamera.SetPosition(pos);
	}
	//�o�l�J�����̍X�V�B
	m_springCamera.Update();
}
void CGameCamera::Notify2DGame() {
	m_camera2D = FindGO<GameCamera2D>("Camera2D");
	m_camera2D->Notify2DGame();
	m_camera2D->Start();
	//�o�l�J���������t���b�V���B
	m_springCamera.Refresh();
	//�o�l�J�������A�N�e�B�u�ɂ���B
	m_isActive = false;
}
void CGameCamera::NotifyGameOver() {
	//�o�l�J���������t���b�V���B
	m_springCamera.Refresh();
	//�o�l�J�������A�N�e�B�u�ɂ���B
	m_isActive = false;
}
void CGameCamera::NotifyGameClear() {
	//�o�l�J���������t���b�V���B
	m_springCamera.Refresh();
	//�o�l�J�������A�N�e�B�u�ɂ���B
	m_isActive = false;
}
void CGameCamera::Notify3DGame() {
	//�o�l�J���������t���b�V���B
	m_springCamera.Refresh();
	//�o�l�J�������A�N�e�B�u�ɂ���B
	m_isActive = true;
}