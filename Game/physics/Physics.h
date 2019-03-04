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
	btCollisionDispatcher*					collisionDispatcher = nullptr;	//!<衝突解決処理。
	btBroadphaseInterface*					overlappingPairCache = nullptr;	//!<ブロードフェーズ。衝突判定の枝切り。
	btSequentialImpulseConstraintSolver*	constraintSolver = nullptr;		//!<コンストレイントソルバー。拘束条件の解決処理。
	btDiscreteDynamicsWorld*				dynamicWorld = nullptr;			//!<ワールド。
	PhysicsDebugDraw						m_debugDraw;
public:
	~CPhysicsWorld();
	void Init();
	void Update();
	void DebubDrawWorld();
	void Release();
	/*!
	* @brief	ダイナミックワールドを取得。
	*/
	btDiscreteDynamicsWorld* GetDynamicWorld()
	{
		return dynamicWorld;
	}
	/*!
	* @brief	剛体を登録。
	*/
	void AddRigidBody(RigidBody& rb);
	/*!
	* @brief	剛体を破棄。
	*/
	void RemoveRigidBody(RigidBody& rb);

	/*!
	* @brief	デバッグ表示のモードを設定する。
	*@param[in]	debugMode		enum btIDebugDraw::DebugDrawModesを参照してください。
	*/
	void SetDebugDrawMode(int debugMode)
	{
		//ワイヤーフレーム描画のみ。
		m_debugDraw.setDebugMode(debugMode);
	}
	/*!
	* @brief	コリジョンオブジェクトをワールドから削除。
	*@param[in]	colliObj	コリジョンオブジェクト。
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
	* @brief	コリジョンオブジェクトをワールドに登録。
	*@param[in]	colliObj	コリジョンオブジェクト。
	*/
	void AddCollisionObject(btCollisionObject& colliObj)
	{
		dynamicWorld->addCollisionObject(&colliObj);
	}
};

extern CPhysicsWorld g_physics;


