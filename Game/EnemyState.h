#pragma once

class Enemy;
class EnemyState
{
protected:
	Enemy*m_enemy;
public:
	EnemyState(Enemy*enemy);
	~EnemyState();

	virtual void StateUpdate() = 0;
	virtual void StateDraw() = 0;
};

