#include "stdafx.h"
#include "EnemyStateSearch.h"
#include"Enemy.h"
#include"Player.h"

EnemyStateSearch::EnemyStateSearch(Enemy* enemy):
EnemyState(enemy)
{
	m_moveSpeed = m_enemy->GetMoveSpeed();
}

EnemyStateSearch::~EnemyStateSearch()
{
}

bool EnemyStateSearch::IsFind() {
	CVector3 enemyForward = CVector3::AxisZ();
	m_enemy->GetRotation().Multiply(enemyForward);
	
	//�G�l�~�[����v���C���[�ɐL�т�x�N�g�������߂�B
	CVector3 toPlayerDir = m_player->GetPosition() - m_enemy->GetPosition();
	//���K�����s���O�ɁA�v���C���[�܂ł̋��������߂Ă����B
	float toPlayerLen = toPlayerDir.Length();
	//���K���I
	toPlayerDir.Normalize();
	//enemyForward��toPlayerDir�Ƃ̓��ς��v�Z����B
	float d = enemyForward.Dot(toPlayerDir);
	//���ς̌��ʂ�acos�֐��ɓn���āAenemyForward��toPlayerDir�̂Ȃ��p�����߂�B
	float angle = acos(d);
	//����p����
	//fabsf�͐�Βl�����߂�֐��I
	//�p�x�̓}�C�i�X�����݂��邩��A��Βl�ɂ���B
	float f = CMath::DegToRad(45.0f);
	float v = fabsf(angle);
	if (v < f
		&& toPlayerLen < 300.0f
		) {
		//�������B
		return true;
	}
	//�����Ă��Ȃ��B
	return false;
}
void EnemyStateSearch::AnimataionControl() {
	//�ҋ@�A�j���[�V����
	m_enemy->SetAnimClip(m_enemy->enAnimationClip_idle);
	m_enemy->GetAnimation().Play(m_enemy->GetAnimClip());
	m_enemy->GetAnimation().Update(GameTime().GetFrameDeltaTime());
}
void EnemyStateSearch::Rotation() {
	
	m_player = m_enemy->GetPlayer();
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX(), 90.0f);
	m_enemy->SetRotaition(qRot);
}
void EnemyStateSearch::Move() {
	//�d��
	m_moveSpeed.y -= 9.8f;
	m_enemy->SetPosition(m_enemy->GetCharaCon().Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed));
}
void EnemyStateSearch::StateUpdate() {
	Move();
	Rotation();
	AnimataionControl();
	m_enemy->GetModel().UpdateWorldMatrix(
		m_enemy->GetPosition(), 
		m_enemy->GetRotation(),
		m_enemy->Scale());
	
	//����X�e�[�g�`�F���W
	//�v���C���̎���p����
	if (IsFind() == true)
	{
		m_enemy->ChangeState(Enemy::State_Attack);
	}
}

void EnemyStateSearch::StateDraw() {
	m_enemy->GetModel().Draw(
		MainCamera().GetViewMatrix(),
		MainCamera().GetProjectionMatrix(),
		m_enemy->GetRenderModel()
);
}