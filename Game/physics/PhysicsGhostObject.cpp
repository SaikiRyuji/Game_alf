#include "stdafx.h"
#include"Physics.h"
#include "PhysicsGhostObject.h"

using namespace std;
PhysicsGhostObject::PhysicsGhostObject()
{
}
void PhysicsGhostObject::Release()
{
	if (m_isRegistPhysicsWorld == true) {
		PhysicsWorld().RemoveCollisionObject(m_ghostObject);
		m_isRegistPhysicsWorld = false;
	}
}
void PhysicsGhostObject::CreateCommon(CVector3 pos, CQuaternion rot)
{
	m_ghostObject.setCollisionShape(m_collider->GetBody());
	btTransform btTrans;
	btTrans.setOrigin({ pos.x, pos.y, pos.z });
	btTrans.setRotation({ rot.x, rot.y, rot.z, rot.w });
	m_ghostObject.setWorldTransform(btTrans);
	m_rot = rot;
	m_pos = pos;
	//ï®óùÉGÉìÉWÉìÇ…ìoò^ÅB
	PhysicsWorld().AddCollisionObject(m_ghostObject);
	m_isRegistPhysicsWorld = true;
}