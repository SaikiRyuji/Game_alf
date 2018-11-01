#include "stdafx.h"
#include "BackGround.h""


BackGround::BackGround()
{
}


BackGround::~BackGround()
{
}

bool BackGround::Start() {
	//cmo�t�@�C���̓ǂݍ��݁B
	m_skinModel.Init(L"Assets/modelData/stageMash1.cmo");
	//���b�V���R���C�_�[���쐬�B
	m_meshCollider.CreateFromSkinModel(m_skinModel, nullptr);
	//���̂̏����쐬�B
	RigidBodyInfo rbInfo;
	rbInfo.pos = CVector3::Zero();
	rbInfo.rot = CQuaternion::Identity();
	rbInfo.collider = &m_meshCollider;
	rbInfo.mass = 0.0f;							//���ʂ�0�ɂ���Ɠ����Ȃ����̂ɂȂ�B
												//�w�i�Ȃǂ̓����Ȃ��I�u�W�F�N�g��0��ݒ肷��Ƃ悢�B
	m_rigidBody.Create(rbInfo);					//�쐬���������g���č��̂��쐬����B
	PhysicsWorld().AddRigidBody(m_rigidBody);	//�쐬�������̂𕨗����[���h�ɒǉ�����B
	m_Scale = { 1.0,1.0,1.0 };
	return true;
}

void BackGround::Update() {
	//���[���h�s��̍X�V�B
	m_skinModel.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), m_Scale);

}

void BackGround::Draw() {
	m_skinModel.Draw(
		MainCamera().GetViewMatrix(),
		MainCamera().GetProjectionMatrix()
	);
}