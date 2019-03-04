/*!
* @brief	ゴーストオブジェクト。
*/
#pragma once
#include"PhysicsObjectBase.h"
/*!
* @brief	ゴーストオブジェクト
*@detail
* ゴーストオブジェクトは剛体がすり抜けるあたり判定のオブジェクトです。
* キャラクターのチェックポイント通過判定、クリア判定などの
* キャラクターがすり抜ける必要のあるあたり判定に使えます。
*/
class PhysicsGhostObject:public PhysicsObjectBase
{
public:
	PhysicsGhostObject();
	~PhysicsGhostObject() {
		Release();
	};
	/*!
	* @brief	ゴーストオブジェクトを解放。
	*@detail
	* 明示的なタイミングでゴーストオブジェクトを削除したい場合に呼び出してください。
	*/
	void Release();
	/*!
	* @brief	引数で渡されたゴーストオブジェクトが自分自身かどうか判定。
	*/
	bool IsSelf(const btCollisionObject& ghost) const
	{
		return &ghost == &m_ghostObject;
	}
	btGhostObject GetSelf() {
		return m_ghostObject;
	}
	/*!
	* @brief	座標を設定。
	*/
	void SetPosition(const CVector3& pos)
	{
		auto& btTrans = m_ghostObject.getWorldTransform();
		btVector3 btPos;
		pos.CopyTo(btPos);
		btTrans.setOrigin(btPos);
	}
	//座標を取得
	CVector3 GetPosition() {
		return m_pos;
	}
	/*!
	* @brief	回転を設定。
	*/
	void SetRotation(const CQuaternion& rot)
	{
		auto& btTrans = m_ghostObject.getWorldTransform();
		btQuaternion btRot;
		rot.CopyTo(btRot);
		btTrans.setRotation(btRot);
	}
	//回転を取得
	CQuaternion GetRotation() {
		return m_rot;
	}
private:
	/*!
	* @brief	ゴースト作成処理の共通処理。
	*/
	void CreateCommon(CVector3 pos, CQuaternion rot);
private:
	bool						m_isRegistPhysicsWorld = false;	//!<物理ワールドに登録しているかどうかのフラグ。
	btGhostObject				m_ghostObject;	//!<ゴースト
	CQuaternion					m_rot = CQuaternion::Identity();
	CVector3					m_pos = CVector3::Zero();
};

