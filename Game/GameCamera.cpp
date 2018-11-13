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
	//�J�������������B
	MainCamera().SetPosition(m_CamPos);
	MainCamera().SetTarget(m_player->GetPosition());
	MainCamera().SetFar(10000.0f);
	m_CamPosLen = m_player->GetPosition() - m_CamPos;
	//�΂˃J�����̏������B
	m_springCamera.Init(
		MainCamera(),		//�΂˃J�����̏������s���J�������w�肷��B
		500.0f,			//�J�����̈ړ����x�̍ő�l�B
		true,				//�J�����ƒn�`�Ƃ̂����蔻�����邩�ǂ����̃t���O�Btrue���Ƃ����蔻����s���B
		1.0f				//�J�����ɐݒ肳��鋅�̃R���W�����̔��a�B��R������true�̎��ɗL���ɂȂ�B
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

	m_rot.MakeRotationFromQuaternion(qRot);

	//���_���v�Z����
	if (!(x == 0 && y == 0)) {
		pos = target + toNewCameraPos;
		m_springCamera.SetTarget(target);
		m_springCamera.SetPosition(pos);
	}
	//�Ə�
	if (g_pad->IsPress(enButtonLB2)) {
	/*	CVector3 vec;
		vec = MainCamera().GetForward()*20.0f;
		target += vec;*/
		target = m_player->GetTarPosition();
		pos = target + toNewCameraPos;
		m_springCamera.SetTarget(target);
		m_springCamera.SetPosition(pos);
	}
	//�o�l�J�����̍X�V�B
	m_springCamera.Update();
}