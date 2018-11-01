#include "stdafx.h"
#include "Enemy.h"
#include"EnemyStateSearch.h"
#include"EnemyStateAttack.h"
#include"Player.h"

Enemy::Enemy()
{
	ChangeState(State_Search);
}


Enemy::~Enemy()
{
}

bool Enemy::Start() {
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	m_position = { 0.0,100.0,50.0 };
	m_charaCon.Init(
		2.0,		//半径
		1.0f,		//高さ
		m_position//初期位置
	);
	InitAnimation();
	m_player = FindGO<Player>("Player");
	return true;
}
void Enemy::InitAnimation() {
	//アニメーション読み込み
	m_animClips[enAnimationClip_idle].Load(L"Assets/animData/idle.tka");
	m_animClips[enAnimationClip_walk].Load(L"Assets/animData/walk.tka");
	m_animClips[enAnimationClip_run].Load(L"Assets/animData/run.tka");
	//アニメーションループ
	m_animClips[enAnimationClip_idle].SetLoopFlag(true);
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	m_animClips[enAnimationClip_run].SetLoopFlag(true);
	//アニメーション初期化
	m_animation.Init(m_model, m_animClips, enAnimationClip_Num);

}
//ステートの切り替えの関数。
void Enemy::ChangeState(State state) {
	//現在の状態を破棄する。
	delete m_pState;
	//探索中
	if (state == State_Search) {
		m_pState = new EnemyStateSearch(this);
	}
	//攻撃中
	else if (state==State_Attack) {
		m_pState = new EnemyStateAttack(this);
	}
}

void Enemy::Update() {
	m_pState->StateUpdate();
}

void Enemy::Draw() {
	m_pState->StateDraw();
}