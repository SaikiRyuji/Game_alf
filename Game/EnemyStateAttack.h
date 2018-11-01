#pragma once
#include"EnemyState.h"
class Enemy;
class EnemyStateAttack :public EnemyState
{
public:
	EnemyStateAttack(Enemy*enemy);
	~EnemyStateAttack();

	void StateUpdate()override;
	void StateDraw()override;
	//移動処理
	void Move();
	//攻撃処理
	void Attack();
	//アニメーション制御
	void AnimataionControl();

private:
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度
};

