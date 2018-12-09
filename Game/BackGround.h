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
	SkinModel m_skinModel;						//�X�L�����f���B
	CVector3 m_position = CVector3::Zero();		//���W�B
	CVector3 m_Scale = CVector3::Zero();		//�g�嗦
	MeshCollider m_meshCollider;				//���b�V���R���C�_�[�B
	RigidBody m_rigidBody;						//���́B
	Player*player = nullptr;					//�v���C���[�|�C���^
	CShaderResourceView m_texture;				//�e�N�X�`��
	CSprite m_sprite;							//�X�v���C�g
	CVector3 m_SpritePos=CVector3::Zero();		//�X�v���C�g���W
	int m_renderModel = 0;
};

