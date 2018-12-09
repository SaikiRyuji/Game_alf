#pragma once
#include"physics\MeshCollider.h"
#include"physics\RigidBody.h"
#include"Player.h"
class BackGround:public GameObject
{
public:
	BackGround();
	~BackGround();
	bool Start()override;
	void Update()override;
	void Render()override;
	void PostRender()override;

	CVector3 GetSpritePos(){
		return m_SpritePos;
	}
private:
	SkinModel m_skinModel;						//スキンモデル。
	CVector3 m_position = CVector3::Zero();		//座標。
	CVector3 m_Scale = CVector3::Zero();		//拡大率
	MeshCollider m_meshCollider;				//メッシュコライダー。
	RigidBody m_rigidBody;						//剛体。
	Player*player = nullptr;					//プレイヤーポインタ
	CShaderResourceView m_texture;				//テクスチャ
	CSprite m_sprite;							//スプライト
	CVector3 m_SpritePos=CVector3::Zero();		//スプライト座標
	int m_renderModel = 0;
};

