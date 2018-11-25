#include "stdafx.h"
#include "EnemyStateAttack.h"
#include"Enemy.h"
#include"Player.h"


EnemyStateAttack::EnemyStateAttack(Enemy*enemy):
	EnemyState(enemy)
{
	m_moveSpeed = m_enemy->GetMoveSpeed();
}


EnemyStateAttack::~EnemyStateAttack()
{
}

void EnemyStateAttack::AnimataionControl() {
	m_enemy->SetAnimClip(m_enemy->enAnimationClip_run);
	m_enemy->GetAnimation().Play(m_enemy->GetAnimClip());
	m_enemy->GetAnimation().Update(GameTime().GetFrameDeltaTime());
}
void EnemyStateAttack::Move() {
	
	m_moveSpeed.y -= 9.8f;
	m_enemy->SetPosition(m_enemy->GetCharaCon().Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed));
}
void EnemyStateAttack::StateUpdate() {
	Move();
	AnimataionControl();
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX(), 90.0f);
	m_enemy->GetModel().UpdateWorldMatrix(
		m_enemy->GetPosition(), 
		qRot,
		m_enemy->Scale());
}

void EnemyStateAttack::StateDraw() {
	m_enemy->GetModel().Draw(
		MainCamera().GetViewMatrix(),
		MainCamera().GetProjectionMatrix(),
		m_enemy->GetRenderModel()
	);
}