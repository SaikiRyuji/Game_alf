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
	//移動処理
	void Move();
	//アニメーション制御
	void AnimataionControl();
	void Rotation();
private:
	CVector3 m_enepla;
	CVector3 m_forward = CVector3::AxisZ();			//エネミーの前方方向
	CVector3 m_moveSpeed=CVector3::Zero();			//移動速度
	Player*m_player = nullptr;						//プレイヤーポインタ
};

