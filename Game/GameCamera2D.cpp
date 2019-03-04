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
	//�΂˃J�����̏������B
	m_springCamera.Init(
		MainCamera(),		//�΂˃J�����̏������s���J�������w�肷��B
		500.0f,			//�J�����̈ړ����x�̍ő�l�B
		false,				//�J�����ƒn�`�Ƃ̂����蔻�����邩�ǂ����̃t���O�Btrue���Ƃ����蔻����s���B
		1.0f				//�J�����ɐݒ肳��鋅�̃R���W�����̔��a�B��R������true�̎��ɗL���ɂȂ�B
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
	//�J�������X�V�B
	//�����_���v�Z����
	CVector3 Pl2DPos = m_pl2D->GetPosition();
	CVector3 target = Pl2DPos;
	//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B
	target.y += 10.0f;
	//���_���v�Z����B
	CVector3 toPos = (m_background->GetZInGhost())*-1.0f*50.0f;
	CVector3 pos = target + toPos;	//�L�����N�^���΂ߏォ�猩�Ă���悤�Ȏ��_�ɂ���B
									//���C���J�����ɒ����_�Ǝ��_��ݒ肷��
	m_springCamera.SetTarget(target);
	m_springCamera.SetPosition(pos);
	float x = g_pad->GetRStickXF();
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), 2.0f*x);
	qRot.Multiply(toPos);
	//���_���v�Z����
	if (!(x == 0)) {
		pos = target + toPos;
		m_springCamera.SetTarget(target);
		m_springCamera.SetPosition(pos);
	}
	m_position = pos;
	m_springCamera.Update();
}
void GameCamera2D::Notify3DGame() {
	//�o�l�J���������t���b�V���B
	m_springCamera.Refresh();
	m_gamecamera->Notify3DGame();
	m_gamecamera->Camera2Dto3D(m_position);
	
	//�o�l�J�������A�N�e�B�u�ɂ���B
	m_isActive = false;
	
}
void GameCamera2D::NotifyGameOver() {
	//�o�l�J���������t���b�V���B
	m_springCamera.Refresh();
	//�o�l�J�������A�N�e�B�u�ɂ���B
	m_isActive = false;
}
void GameCamera2D::NotifyGameClear() {
	//�o�l�J���������t���b�V���B
	m_springCamera.Refresh();
	//�o�l�J�������A�N�e�B�u�ɂ���B
	m_isActive = false;
}
void GameCamera2D::Notify2DGame() {
	//�o�l�J���������t���b�V���B
	m_springCamera.Refresh();
	//�o�l�J�������A�N�e�B�u�ɂ���B
	m_isActive = true;
}