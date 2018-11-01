#include "stdafx.h"
#include "SphereCollider.h"


CSphereCollider::CSphereCollider():shape(NULL)
{
}


CSphereCollider::~CSphereCollider()
{
}
/*!
* @brief	球体コライダーを作成。
*/
void CSphereCollider::Create(const float radius) {
	shape = new btSphereShape(radius);
}