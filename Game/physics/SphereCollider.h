/*!
*@brief 球体コライダー
*/
#pragma once
#include"physics\ICollider.h"

class CSphereCollider :public ICollider
{
public:
	CSphereCollider();
	~CSphereCollider();
	/*!
	*@brief 球体コライダー作成
	*/
	void Create(const float radius);
	btCollisionShape* GetBody() const override
	{
		return shape;
	}

private:
	btSphereShape* shape;
};

