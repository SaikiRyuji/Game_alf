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
	void Draw()override;

private:
	SkinModel m_skinModel;						//�X�L�����f���B
	CVector3 m_position = CVector3::Zero();		//���W�B
	CVector3 m_Scale = CVector3::Zero();		//�g�嗦
	MeshCollider m_meshCollider;				//���b�V���R���C�_�[�B
	RigidBody m_rigidBody;						//���́B
	Player*player = nullptr;					//�v���C���[�|�C���^
};

