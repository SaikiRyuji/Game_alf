#pragma once
#include"EnemyState.h"

class Player;
class Enemy;
class EnemyStateSearch:public EnemyState
{
public:
	EnemyStateSearch(Enemy* enemy);
	~EnemyStateSearch();
	void StateUpdate()override;
	void StateDraw()override;
	//�ړ�����
	void Move();
	//�A�j���[�V��������
	void AnimataionControl();
	void Rotation();
private:
	CVector3 m_enepla;
	CVector3 m_forward = CVector3::AxisZ();			//�G�l�~�[�̑O������
	CVector3 m_moveSpeed=CVector3::Zero();			//�ړ����x
	Player*m_player = nullptr;						//�v���C���[�|�C���^
};

