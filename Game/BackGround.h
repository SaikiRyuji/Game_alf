#pragma once
#include"physics\MeshCollider.h"
#include"physics\RigidBody.h"
#include"Player.h"
#include"physics\PhysicsGhostObject.h"
class BackGround:public GameObject
{
public:
	BackGround();
	~BackGround();
	bool Start()override;
	void Update()override;
	void Render()override;
	void PostRender()override;
	bool IsHit(CharacterController& charaCon);
	//スプライト座標取得
	CVector3 GetSpritePos(){
		return m_SpritePos;
	}
	//ゴーストの基点座標取得
	CVector3 GetGhostPos() {
		return m_GhostPos;
	}
	//ゴーストの回転座標
	CQuaternion GetGhostRotation() {
		return m_GhostRot;
	}
	//ゴーストのx軸を取得
	CVector3 GetXInGhost() {
		return m_xInGhost;
	}
	//ゴーストのz軸を取得
	CVector3 GetZInGhost() {
		return m_zInGhost;
	}
private:
	SkinModel m_skinModel;									//スキンモデル。
	CVector3 m_position = CVector3::Zero();					//座標。
	CVector3 m_Scale = CVector3::Zero();					//拡大率
	MeshCollider m_meshCollider;							//メッシュコライダー。
	RigidBody m_rigidBody;									//剛体。
	Player*player = nullptr;								//プレイヤーポインタ
	CShaderResourceView m_texture;							//テクスチャ
	CSprite m_sprite;										//スプライト
	CVector3 m_SpritePos=CVector3::Zero();					//スプライト座標
	int m_renderModel = 0;
	std::vector< PhysicsGhostObject*> m_ghotsObjects;		//ゴーストオブジェクト。
	CVector3 m_GhostPos=CVector3::Zero();					//ゴーストの座標
	CQuaternion m_GhostRot=CQuaternion::Identity();			//
	CVector3 m_xInGhost = CVector3::Zero();					//ゴーストのx軸
	CVector3 m_zInGhost = CVector3::Zero();					//ゴーストのz軸
};

