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
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	m_position = { 0.0,100.0,50.0 };
	m_charaCon.Init(
		2.0,		//���a
		1.0f,		//����
		m_position//�����ʒu
	);
	InitAnimation();
	m_player = FindGO<Player>("Player");
	return true;
}
void Enemy::InitAnimation() {
	//�A�j���[�V�����ǂݍ���
	m_animClips[enAnimationClip_idle].Load(L"Assets/animData/idle.tka");
	m_animClips[enAnimationClip_walk].Load(L"Assets/animData/walk.tka");
	m_animClips[enAnimationClip_run].Load(L"Assets/animData/run.tka");
	//�A�j���[�V�������[�v
	m_animClips[enAnimationClip_idle].SetLoopFlag(true);
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	m_animClips[enAnimationClip_run].SetLoopFlag(true);
	//�A�j���[�V����������
	m_animation.Init(m_model, m_animClips, enAnimationClip_Num);

}
//�X�e�[�g�̐؂�ւ��̊֐��B
void Enemy::ChangeState(State state) {
	//���݂̏�Ԃ�j������B
	delete m_pState;
	//�T����
	if (state == State_Search) {
		m_pState = new EnemyStateSearch(this);
	}
	//�U����
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