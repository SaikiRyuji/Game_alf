#pragma once
#include "character/CharacterController.h"
class Enemy;
class BackGround;
class CGameCamera;
class GameCamera2D;
class Player :public GameObject
{
public:
	Player();
	~Player();
	bool Start()override;
	void Update()override;
	//描画処理
	void Render()override;
	void PostRender()override;
	//移動処理
	void Move();
	//回転処理
	void Rotation();
	//回避処理
	void Avoid();
	//アニメーション初期化
	void InitAnimation();
	//アニメーション制御
	void AnimataionControl();
	//アクション処理
	void Action();

	CVector3 GetPosition() {
		return m_position;
	}
	CQuaternion GetRotation() {
		return m_rotation;
	}
	CVector3 GetTarPosition() {
		return m_tarpos;
	}
	bool Get2DFlag() {
		return m_Flag2D;
	}
	CharacterController& GetCharaCon() {
		return m_charaCon;
	}
	void SetPosition2D(CVector3 position) {
		m_position.x = position.x-1.0;
		m_position.y = position.y;
	}
	void Set2DFlag(bool tf) {
		m_Flag2D = tf;
	}
	void SetMoveSped(CVector3 speed) {
		m_moveSpeed = speed;
	}
private:
	enum EnAnimationClip {
		enAnimationClip_idle,		//待機アニメーション。
		enAnimationClip_run,		//走りアニメーション。
		enAnimationClip_walk,		//歩きアニメーション。
		enAnimationClip_jump,		//ジャンプアニメーション。
		enAnimationClip_attack,		//攻撃アニメーション。
		enAnimationClip_defense,	//防御アニメーション。
		enAnimationClip_item,		//アイテム使用アニメーション。
		enAnimationClip_Num,		//アニメーションクリップの数。
	};
	bool m_Flag2D = false;								//2D状態かどうか？
	CVector3 m_tarpos = CVector3::Zero();
	AnimationClip m_animClips[enAnimationClip_Num];		//アニメーションクリップ。
	Animation m_animation;								//アニメーション
	SkinModel m_model;									//スキンモデル
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度
	CVector3 m_position = CVector3::Zero();				//座標
	CVector3 m_sppos = CVector3::Zero();				//スプライト座標
	CharacterController m_charaCon;						//キャラクターコントローラー
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CSprite m_sprite;									//スプライト
	CShaderResourceView m_spritetex;					//スプライトテクスチャ
	bool m_Avoidf = false;								//回避Flag
	CMatrix m_rot;										//回転行列
	float m_friction;							//摩擦力
	Enemy*m_enemy=nullptr;								//エネミーポインタ
	BackGround*m_background = nullptr;
	CGameCamera*m_gamecamera = nullptr;
	GameCamera2D*m_Camera2D = nullptr;
};
