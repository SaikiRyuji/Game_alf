/*!
*@brief ���̃R���C�_�[
*/
#pragma once
#include"physics\ICollider.h"

class CSphereCollider :public ICollider
{
public:
	CSphereCollider();
	~CSphereCollider();
	/*!
	*@brief ���̃R���C�_�[�쐬
	*/
	void Create(const float radius);
	btCollisionShape* GetBody() const override
	{
		return shape;
	}

private:
	btSphereShape* shape;
};

