#pragma once
#include"EnemyState.h"
#include "character/CharacterController.h"
class Player;
class Enemy:public GameObject
{
public:
	enum EnAnimationClip {
		enAnimationClip_idle,		//�ҋ@�A�j���[�V����
		enAnimationClip_run,		//����A�j���[�V����
		enAnimationClip_walk,		//�����A�j���[�V����
		enAnimationClip_Num,		//�A�j���[�V�����N���b�v��
	};
	EnAnimationClip m_AnimClips=enAnimationClip_idle;
	enum State {
		State_Search,		//�p�j��
		State_Attack,		//�U����
	};
	Enemy();
	~Enemy();
	bool Start()override;
	void Update()override;
	//�`�揈��
	void Draw() override;
	//�A�j���[�V����������
	void InitAnimation();
	//�X�e�[�g�ύX
	//State�@�X�e�[�g
	void ChangeState(State state);
	//�G�l�~�[�̗l�X�Ȋg�嗦
	CVector3 Scale();

	//�G�l�~�[���W�擾
	CVector3 GetPosition() {
		return m_position;
	}
	//�G�l�~�[���W�ύX
	//CVector3		position���W
	void SetPosition(CVector3 position) {
		m_position = position;
	}
	//�G�l�~�[�̉�]�ύX
	//CQuaternion	��]�N�H�[�^�j�I��
	void SetRotaition(CQuaternion rotaition) {
		m_rotation = rotaition;
	}
	//�G�l�~�[���f���擾
	SkinModel& GetModel() {
		return m_model;
	}
	//�G�l�~�[��]�擾
	CQuaternion GetRotation() {
		return m_rotation;
	}
	//�G�l�~�[�ړ����x�擾
	CVector3 GetMoveSpeed() {
		return m_moveSpeed;
	}
	//�G�l�~�[�L�����N�^�[�R���g���[���擾
	CharacterController& GetCharaCon() {
		return m_charaCon;
	}
	//�G�l�~�[�A�j���[�V�����擾
	Animation& GetAnimation() {
		return m_animation;
	}
	//�G�l�~�[�A�j���[�V�����N���b�v�擾
	EnAnimationClip GetAnimClip(){
		return m_AnimClips;
	}
	//�G�l�~�[�A�j���[�V�����ύX
	//EnAnimationClip		�A�j���[�V�����N���b�v
	void SetAnimClip(EnAnimationClip Clip) {
		m_AnimClips = Clip;
	}
	void RotMultiply(CVector3 rot) {
		m_rotation.Multiply(rot);
	}
	int GetRenderModel() {
		return m_renderModel;
	}
	////�g�嗦��ݒ�
	////CVector3		�g�嗦
	//void SetScale(CVector3 scale) {
	//	m_Scale = scale;
	//}
	//FindGo�Ō������v���C���[�擾
	Player* GetPlayer() {
		return m_player;
	}
private:
	AnimationClip m_animClips[enAnimationClip_Num];		//�A�j���[�V�����N���b�v�B
	Animation m_animation;								//�A�j���[�V����
	EnemyState* m_pState = nullptr;						//�G�l�~�[�X�e�[�g
	SkinModel m_model;									//�X�L�����f��
	CVector3 m_moveSpeed = CVector3::Zero();			//�ړ����x
	CVector3 m_position = CVector3::Zero();				//���W
	CQuaternion m_rotation = CQuaternion::Identity();	//��]
	CharacterController m_charaCon;						//�L�����N�^�[�R���g���[��
	CVector3 m_Scale;										//�g�嗦
	Player* m_player=nullptr;							//�v���C���[�|�C���^
	int m_renderModel = 0;
};

