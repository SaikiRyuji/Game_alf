#pragma once
#include "character/CharacterController.h"
class Enemy;
class BackGround;
class Player :public GameObject
{
public:
	Player();
	~Player();
	bool Start()override;
	void Update()override;
	//�`�揈��
	void Render()override;
	void PostRender()override;
	//�ړ�����
	void Move();
	//��]����
	void Rotation();
	//�������
	void Avoid();
	//�A�j���[�V����������
	void InitAnimation();
	//�A�j���[�V��������
	void AnimataionControl();
	//�A�N�V��������
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
private:
	enum EnAnimationClip {
		enAnimationClip_idle,		//�ҋ@�A�j���[�V�����B
		enAnimationClip_run,		//����A�j���[�V�����B
		enAnimationClip_walk,		//�����A�j���[�V�����B
		enAnimationClip_jump,		//�W�����v�A�j���[�V�����B
		enAnimationClip_attack,		//�U���A�j���[�V�����B
		enAnimationClip_defense,	//�h��A�j���[�V�����B
		enAnimationClip_item,		//�A�C�e���g�p�A�j���[�V�����B
		enAnimationClip_Num,		//�A�j���[�V�����N���b�v�̐��B
	};
	CVector3 m_tarpos = CVector3::Zero();
	AnimationClip m_animClips[enAnimationClip_Num];		//�A�j���[�V�����N���b�v�B
	Animation m_animation;								//�A�j���[�V����
	SkinModel m_model;									//�X�L�����f��
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x
	CVector3 m_position = CVector3::Zero();				//���W
	CVector3 m_sppos = CVector3::Zero();				//�X�v���C�g���W
	CharacterController m_charaCon;						//�L�����N�^�[�R���g���[���[
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CSprite m_sprite;									//�X�v���C�g
	CShaderResourceView m_spritetex;					//�X�v���C�g�e�N�X�`��
	bool m_Avoidf = false;								//���Flag
	CMatrix m_rot;										//��]�s��
	float m_friction;							//���C��
	Enemy*m_enemy=nullptr;								//�G�l�~�[�|�C���^
	BackGround*m_background = nullptr;
};
