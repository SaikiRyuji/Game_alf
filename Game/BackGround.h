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
	//�X�v���C�g���W�擾
	CVector3 GetSpritePos(){
		return m_SpritePos;
	}
	//�S�[�X�g�̊�_���W�擾
	CVector3 GetGhostPos() {
		return m_GhostPos;
	}
	//�S�[�X�g�̉�]���W
	CQuaternion GetGhostRotation() {
		return m_GhostRot;
	}
	//�S�[�X�g��x�����擾
	CVector3 GetXInGhost() {
		return m_xInGhost;
	}
	//�S�[�X�g��z�����擾
	CVector3 GetZInGhost() {
		return m_zInGhost;
	}
private:
	SkinModel m_skinModel;									//�X�L�����f���B
	CVector3 m_position = CVector3::Zero();					//���W�B
	CVector3 m_Scale = CVector3::Zero();					//�g�嗦
	MeshCollider m_meshCollider;							//���b�V���R���C�_�[�B
	RigidBody m_rigidBody;									//���́B
	Player*player = nullptr;								//�v���C���[�|�C���^
	CShaderResourceView m_texture;							//�e�N�X�`��
	CSprite m_sprite;										//�X�v���C�g
	CVector3 m_SpritePos=CVector3::Zero();					//�X�v���C�g���W
	int m_renderModel = 0;
	std::vector< PhysicsGhostObject*> m_ghotsObjects;		//�S�[�X�g�I�u�W�F�N�g�B
	CVector3 m_GhostPos=CVector3::Zero();					//�S�[�X�g�̍��W
	CQuaternion m_GhostRot=CQuaternion::Identity();			//
	CVector3 m_xInGhost = CVector3::Zero();					//�S�[�X�g��x��
	CVector3 m_zInGhost = CVector3::Zero();					//�S�[�X�g��z��
};

