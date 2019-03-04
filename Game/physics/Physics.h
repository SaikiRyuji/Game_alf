#pragma once
#include"CollisionAttr.h"
#include"PhysicsDebugDraw.h"
#include"RigidBody.h"
#include"../character/CharacterController.h"
class CPhysicsWorld
{
	struct ContactResultCallback : public btCollisionWorld::ContactResultCallback {
		using ContantTestCallback = std::function<void(const btCollisionObject& contactCollisionObject)>;
		ContantTestCallback  m_cb;
		btCollisionObject* m_me = nullptr;
		virtual	btScalar	addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1) override
		{
			if (m_me == colObj0Wrap->getCollisionObject()) {
				m_cb(*colObj1Wrap->getCollisionObject());
			}
			return 0.0f;
		}
	};
	btDefaultCollisionConfiguration*		collisionConfig = nullptr;
	btCollisionDispatcher*					collisionDispatcher = nullptr;	//!<�Փˉ��������B
	btBroadphaseInterface*					overlappingPairCache = nullptr;	//!<�u���[�h�t�F�[�Y�B�Փ˔���̎}�؂�B
	btSequentialImpulseConstraintSolver*	constraintSolver = nullptr;		//!<�R���X�g���C���g�\���o�[�B�S�������̉��������B
	btDiscreteDynamicsWorld*				dynamicWorld = nullptr;			//!<���[���h�B
	PhysicsDebugDraw						m_debugDraw;
public:
	~CPhysicsWorld();
	void Init();
	void Update();
	void DebubDrawWorld();
	void Release();
	/*!
	* @brief	�_�C�i�~�b�N���[���h���擾�B
	*/
	btDiscreteDynamicsWorld* GetDynamicWorld()
	{
		return dynamicWorld;
	}
	/*!
	* @brief	���̂�o�^�B
	*/
	void AddRigidBody(RigidBody& rb);
	/*!
	* @brief	���̂�j���B
	*/
	void RemoveRigidBody(RigidBody& rb);

	/*!
	* @brief	�f�o�b�O�\���̃��[�h��ݒ肷��B
	*@param[in]	debugMode		enum btIDebugDraw::DebugDrawModes���Q�Ƃ��Ă��������B
	*/
	void SetDebugDrawMode(int debugMode)
	{
		//���C���[�t���[���`��̂݁B
		m_debugDraw.setDebugMode(debugMode);
	}
	/*!
	* @brief	�R���W�����I�u�W�F�N�g�����[���h����폜�B
	*@param[in]	colliObj	�R���W�����I�u�W�F�N�g�B
	*/
	void RemoveCollisionObject(btCollisionObject& colliObj)
	{
		dynamicWorld->removeCollisionObject(&colliObj);
	}
	void ConvexSweepTest(
		const btConvexShape* castShape,
		const btTransform& convexFromWorld,
		const btTransform& convexToWorld,
		btCollisionWorld::ConvexResultCallback& resultCallback,
		btScalar allowedCcdPenetration = 0.0f
	)
	{
		dynamicWorld->convexSweepTest(castShape, convexFromWorld, convexToWorld, resultCallback, allowedCcdPenetration);
	}
	void ContactText(
		btCollisionObject* colObj, 
		std::function<void(const btCollisionObject& contactCollisionObject)> cb
	)
	{
		ContactResultCallback myContactResultCallback;
		myContactResultCallback.m_cb = cb;
		myContactResultCallback.m_me = colObj;
		dynamicWorld->contactTest(colObj, myContactResultCallback);
	}
	void CPhysicsWorld::ContactTest(
		RigidBody& rb,
		std::function<void(const btCollisionObject& contactCollisionObject)> cb
	)
	{
		ContactText(rb.GetBody(), cb);
	}
	void ContactTest(
		CharacterController& charaCon,
		std::function<void(const btCollisionObject& contactCollisionObject)> cb
	)
	{
		ContactTest(*charaCon.GetRigidBody(), cb);
	}
	/*!
	* @brief	�R���W�����I�u�W�F�N�g�����[���h�ɓo�^�B
	*@param[in]	colliObj	�R���W�����I�u�W�F�N�g�B
	*/
	void AddCollisionObject(btCollisionObject& colliObj)
	{
		dynamicWorld->addCollisionObject(&colliObj);
	}
};

extern CPhysicsWorld g_physics;


