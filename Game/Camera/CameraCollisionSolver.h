/*!
*@brief	�O�l�̎��_�̃Q�[���J�����R���W�����\���o�[
*/

#pragma once
#include"physics/SphereCollider.h"
class CCameraCollisionSolver
{
public:
	CCameraCollisionSolver();
	~CCameraCollisionSolver();

	void Init(float radius);

	bool Execute(CVector3& result, const CVector3& position, const CVector3& target);
private:
	CSphereCollider m_collider;
	float m_radius = 0.0f;
	int m_mapObj = 32;
};

