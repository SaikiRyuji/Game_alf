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
	
	//�G�l�~�[�̑O���������߂�
	CMatrix mRot;
	mRot.MakeRotationFromQuaternion(m_enemy->GetRotation());
	m_forward.x = mRot.m[2][0];
	m_forward.y = mRot.m[2][1];
	m_forward.z = mRot.m[2][2];
	
	//�G�l�~�[����v���C���[�Ɍ������x�N�g�� 
	CVector3 toPlayer = m_player->GetPosition()-m_enemy->GetPosition();
	
	if (toPlayer.Length() < 40.0f);
	{
		//toPlayer���K�� 
		toPlayer.Normalize();
		//m_forward��toPlayer�̓��� 
		float angle = toPlayer.Dot(m_forward);

		angle = acosf(angle);
		//������̏���
		if (fabsf(angle) < CMath::PI*0.25) {
			
		}
	}
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
		CVector3{ 0.1f,0.1f,0.1f });
	
	//����X�e�[�g�`�F���W
	if (g_pad->IsTrigger(enButtonX))
	{
		m_enemy->ChangeState(Enemy::State_Attack);
	}
}

void EnemyStateSearch::StateDraw() {
	m_enemy->GetModel().Draw(
		MainCamera().GetViewMatrix(),
		MainCamera().GetProjectionMatrix());
}