#include "stdafx.h"
#include "Player.h"
#include"Enemy.h"
#include"BackGround.h"
Player::Player()
{
}


Player::~Player()
{
}

bool Player::Start() {
	m_position = { 0.0f,1000.0f,0.0f };
	m_charaCon.Init(
		2.0,		//���a
		1.0f,		//����
		m_position//�����ʒu
	);
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	//dds�t�@�C���̓ǂݍ���
	m_spritetex.CreateFromDDSTextureFromFile(L"Assets/sprite/hpd.dds");
	//�e�N�X�`���̏�����
	m_sprite.Init(m_spritetex, 1, 1);
	//�A�j���[�V�����ǂݍ��ݏ�����
	InitAnimation();
	m_animation.Play(enAnimationClip_idle);
	m_enemy = FindGO<Enemy>("Enemy");
	m_background = FindGO<BackGround>("background");
	return true;
}
void Player::InitAnimation() {
	//�A�j���[�V�����ǂݍ���
	m_animClips[enAnimationClip_idle].Load(L"Assets/animData/idle.tka");
	m_animClips[enAnimationClip_walk].Load(L"Assets/animData/walk.tka");
	m_animClips[enAnimationClip_run].Load(L"Assets/animData/run.tka");
	//�A�j���[�V�������[�v
	m_animClips[enAnimationClip_idle].SetLoopFlag(true);
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	m_animClips[enAnimationClip_run].SetLoopFlag(true);
	//�A�j���[�V����������
	m_animation.Init(m_model, m_animClips, enAnimationClip_Num);
}
void Player::AnimataionControl(){
	if (!m_charaCon.IsJump()) {
		if (m_moveSpeed.LengthSq() > 20.0f * 20.0f) {
			//����A�j���[�V����
			m_animation.Play(enAnimationClip_run, 0.2f);
		}
		else if (m_moveSpeed.LengthSq() > 2.5f * 2.5f) {
			//�����A�j���[�V����
			m_animation.Play(enAnimationClip_walk, 0.2f);
		}
		else {
			//�ҋ@�A�j���[�V����
			m_animation.Play(enAnimationClip_idle, 0.2f);
		}
	}
	m_animation.Update(GameTime().GetFrameDeltaTime());
}
void Player::Move() {
	//�d��
	const float gravity = 9.8f;
	//���x
	const float Speed = 90.0f;
	//�W�����v���̍���
	const float jump = 120.0f;
	//���C��
	m_friction = -3.0f;
	//���X�e�B�b�N�̓��͗ʂ��󂯎��B
	float lStick_x = g_pad->GetLStickXF();
	float lStick_y = g_pad->GetLStickYF();
	//�J�����̑O�������ƉE�������擾�B
	CVector3 cameraForward = MainCamera().GetForward();
	CVector3 cameraRight = MainCamera().GetRight();
	//XZ���ʂł̑O�������A�E�����ɕϊ�����B
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	//XZ�����̈ړ����x���N���A�B
	cameraForward *= lStick_y *Speed *GameTime().GetFrameDeltaTime();	//�������ւ̈ړ����x�����B	
	cameraRight *= lStick_x * Speed*GameTime().GetFrameDeltaTime();	//�E�����ւ̈ړ����x�����Z�B
	
	//�W�����v
	if (g_pad->IsTrigger(enButtonA) && m_charaCon.IsOnGround() == true) {
		m_moveSpeed.y += jump;
	}
	//��i�W�����v
	if (g_pad->IsTrigger(enButtonA) && m_charaCon.IsJump()&&!m_charaCon.Is2ndJump()) {
		m_moveSpeed.y += jump;
		m_charaCon.Set2ndJump();
	}
	//���C
	CVector3 masa = m_moveSpeed;
	if (m_charaCon.IsJump()) {
		//�W�����v���A���C�͂�������
		m_friction = -1.0f;
		masa *= m_friction;
	}
	else {
		//���̑�
		masa *= m_friction;
	}
	//�ړ����x�ɖ��C��^����
	m_moveSpeed.x += masa.x * GameTime().GetFrameDeltaTime();
	m_moveSpeed.z += masa.z * GameTime().GetFrameDeltaTime();
	m_moveSpeed += cameraForward;
	m_moveSpeed += cameraRight;
	//�W�����v��
	if (g_pad->IsPress(enButtonB) 
		&& m_charaCon.IsJump()) {
		//����������(�d�͂�5�{)�ɐݒ�
		m_moveSpeed.y -= gravity*5.0f;
	}
	else {
		m_moveSpeed.y -= gravity;
	}
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);
	if (m_position.y<= -400.0f) {
		m_position = { 0.0f,30.0f,0.0f };
	}
}
void Player::Rotation() {

	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		return;
	}
	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
	m_rotation.SetRotation(CVector3::AxisY(), angle);

	m_rot.MakeRotationFromQuaternion(m_rotation);
	m_tarpos.x = m_rot.m[2][0] * 5.0f + m_position.x;
	m_tarpos.y = m_rot.m[2][1] * 5.0f + m_position.y;
	m_tarpos.z = m_rot.m[2][2] * 5.0f + m_position.z;
}
void Player::Avoid() {
	//�G�l�~�[����v���C���[�̃x�N�g��
	CVector3 EtoPpos;
	EtoPpos = m_enemy->GetPosition() - m_position;
	//�G�l�~�[����v���C���[�̒���
	float EtoPlen;
	EtoPlen =EtoPpos.Length();
	//�e�N�X�`���\���t���O
	if (EtoPlen < 10.0f && !m_Avoidf) {
		m_Avoidf = true;
	}
	else if((EtoPlen > 10.0f && m_Avoidf)) {
		m_Avoidf = false;
	}

	//�܂�����i�K�@�@/�G�l�~�[�̌��Ɉړ����鏈��
	if (m_Avoidf&&g_pad->IsTrigger(enButtonB))
	{
		m_rot.MakeRotationFromQuaternion(m_enemy->GetRotation());
		m_position.x = -m_rot.m[2][0] * 40.0f + m_enemy->GetPosition().x;
		m_position.z = -m_rot.m[2][2] * 40.0f + m_enemy->GetPosition().z;
		m_charaCon.SetPosition(m_position);

	}

}
void Player::Action() {
	CVector3 SpriteToPos = m_position - m_background->GetSpritePos();
	float StoPLen=SpriteToPos.Length();
	if (StoPLen<=10.0f&&g_pad->IsTrigger(enButtonB))
	{ 

	}
}
void Player::Update()
{
	AnimataionControl();
	Move();
	Rotation();
	Avoid();

	CQuaternion qRot=CQuaternion::Identity();
	qRot.SetRotationDeg(CVector3::AxisX(), 90.0f);
	qRot.Multiply(m_rotation, qRot);
	//���[���h�s��̍X�V�B
	if (g_pad->IsTrigger(enButtonDown))
	{
		m_model.SetSpecPow(0.0f);
	}
	m_model.UpdateWorldMatrix(m_position, qRot,CVector3 { 0.1f,0.1f,0.1f });
	m_sppos.y = 1.0f;
	m_sprite.Update(m_sppos, CQuaternion::Identity(), CVector3::One());
}

void Player::Draw()
{
	m_renderModel = 1;
	m_model.Draw(
		MainCamera().GetViewMatrix(), 
		MainCamera().GetProjectionMatrix(),
		m_renderModel
	);
	m_renderModel = 0;
	m_model.Draw(
		MainCamera().GetViewMatrix(),
		MainCamera().GetProjectionMatrix(),
		m_renderModel
	);
}
void Player::PostDraw() {
	if (g_pad->IsPress(enButtonLB2)) {
		m_sprite.Draw(
			MainCamera2D().GetViewMatrix(),
			MainCamera2D().GetProjectionMatrix()
		);
	}
}