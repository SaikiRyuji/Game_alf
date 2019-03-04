#include "stdafx.h"
#include "PhysicsObjectBase.h"
#include"SphereCollider.h"
#include"BoxCollider.h"
#include"MeshCollider.h"
#include"CapsuleCollider.h"
using namespace std;
void PhysicsObjectBase::CreateBox(CVector3 pos, CQuaternion rot, CVector3 size)
{
	Release();
	auto boxCollider = std::make_unique<BoxCollider>();
	boxCollider->Create(size);
	m_collider = std::move(boxCollider);
	CreateCommon(pos, rot);
}
void PhysicsObjectBase::CreateCapsule(CVector3 pos, CQuaternion rot, float radius, float height)
{
	Release();
	auto capusuleCollider = std::make_unique<CapsuleCollider>();
	capusuleCollider->Create(radius, height);
	m_collider = move(capusuleCollider);
	CreateCommon(pos, rot);
}

void PhysicsObjectBase::CreateSphere(CVector3 pos, CQuaternion rot, float radius)
{
	Release();
	auto sphereCollider = std::make_unique<CSphereCollider>();
	sphereCollider->Create(radius);
	m_collider = move(sphereCollider);
	CreateCommon(pos, rot);
}
void PhysicsObjectBase::CreateMesh(CVector3 pos, CQuaternion rot, CVector3 scale, const SkinModel& skinModel)
{
	Release();
	CMatrix mScale;
	mScale.MakeScaling(scale);
	auto meshCollider = std::make_unique<MeshCollider>();
	meshCollider->CreateFromSkinModel(skinModel, &mScale);
	m_collider = std::move(meshCollider);
	CreateCommon(
		pos,
		rot
	);

}