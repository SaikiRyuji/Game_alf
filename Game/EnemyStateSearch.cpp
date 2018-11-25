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
	
	//エネミーからプレイヤーに伸びるベクトルを求める。
	CVector3 toPlayerDir = m_player->GetPosition() - m_enemy->GetPosition();
	//正規化を行う前に、プレイヤーまでの距離を求めておく。
	float toPlayerLen = toPlayerDir.Length();
	//正規化！
	toPlayerDir.Normalize();
	//enemyForwardとtoPlayerDirとの内積を計算する。
	float d = enemyForward.Dot(toPlayerDir);
	//内積の結果をacos関数に渡して、enemyForwardとtoPlayerDirのなす角を求める。
	float angle = acos(d);
	//視野角判定
	//fabsfは絶対値を求める関数！
	//角度はマイナスが存在するから、絶対値にする。
	float f = CMath::DegToRad(45.0f);
	float v = fabsf(angle);
	if (v < f
		&& toPlayerLen < 300.0f
		) {
		//見つけた。
		return true;
	}
	//見つけていない。
	return false;
}
void EnemyStateSearch::AnimataionControl() {
	//待機アニメーション
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
	//重力
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
	
	//試作ステートチェンジ
	//プレイヤの視野角判定
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