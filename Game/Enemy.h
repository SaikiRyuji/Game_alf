#pragma once
#include"EnemyState.h"
#include "character/CharacterController.h"
class Player;
class Enemy:public GameObject
{
public:
	enum EnAnimationClip {
		enAnimationClip_idle,		//待機アニメーション
		enAnimationClip_run,		//走りアニメーション
		enAnimationClip_walk,		//歩きアニメーション
		enAnimationClip_Num,		//アニメーションクリップ数
	};
	EnAnimationClip m_AnimClips=enAnimationClip_idle;
	enum State {
		State_Search,		//徘徊中
		State_Attack,		//攻撃中
	};
	Enemy();
	~Enemy();
	bool Start()override;
	void Update()override;
	//描画処理
	void Draw() override;
	//アニメーション初期化
	void InitAnimation();
	//ステート変更
	//State　ステート
	void ChangeState(State state);
	//エネミーの様々な拡大率
	CVector3 Scale();

	//エネミー座標取得
	CVector3 GetPosition() {
		return m_position;
	}
	//エネミー座標変更
	//CVector3		position座標
	void SetPosition(CVector3 position) {
		m_position = position;
	}
	//エネミーの回転変更
	//CQuaternion	回転クォータニオン
	void SetRotaition(CQuaternion rotaition) {
		m_rotation = rotaition;
	}
	//エネミーモデル取得
	SkinModel& GetModel() {
		return m_model;
	}
	//エネミー回転取得
	CQuaternion GetRotation() {
		return m_rotation;
	}
	//エネミー移動速度取得
	CVector3 GetMoveSpeed() {
		return m_moveSpeed;
	}
	//エネミーキャラクターコントローラ取得
	CharacterController& GetCharaCon() {
		return m_charaCon;
	}
	//エネミーアニメーション取得
	Animation& GetAnimation() {
		return m_animation;
	}
	//エネミーアニメーションクリップ取得
	EnAnimationClip GetAnimClip(){
		return m_AnimClips;
	}
	//エネミーアニメーション変更
	//EnAnimationClip		アニメーションクリップ
	void SetAnimClip(EnAnimationClip Clip) {
		m_AnimClips = Clip;
	}
	void RotMultiply(CVector3 rot) {
		m_rotation.Multiply(rot);
	}
	int GetRenderModel() {
		return m_renderModel;
	}
	////拡大率を設定
	////CVector3		拡大率
	//void SetScale(CVector3 scale) {
	//	m_Scale = scale;
	//}
	//FindGoで見つけたプレイヤー取得
	Player* GetPlayer() {
		return m_player;
	}
private:
	AnimationClip m_animClips[enAnimationClip_Num];		//アニメーションクリップ。
	Animation m_animation;								//アニメーション
	EnemyState* m_pState = nullptr;						//エネミーステート
	SkinModel m_model;									//スキンモデル
	CVector3 m_moveSpeed = CVector3::Zero();			//移動速度
	CVector3 m_position = CVector3::Zero();				//座標
	CQuaternion m_rotation = CQuaternion::Identity();	//回転
	CharacterController m_charaCon;						//キャラクターコントローラ
	CVector3 m_Scale;										//拡大率
	Player* m_player=nullptr;							//プレイヤーポインタ
	int m_renderModel = 0;
};

