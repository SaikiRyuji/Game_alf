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
	//�ړ�����
	void Move();
	//�U������
	void Attack();
	//�A�j���[�V��������
	void AnimataionControl();

private:
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x
};

