#include "stdafx.h"
#include "SphereCollider.h"


CSphereCollider::CSphereCollider():shape(NULL)
{
}


CSphereCollider::~CSphereCollider()
{
}
/*!
* @brief	���̃R���C�_�[���쐬�B
*/
void CSphereCollider::Create(const float radius) {
	shape = new btSphereShape(radius);
}