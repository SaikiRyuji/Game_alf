#include "stdafx.h"
#include "BackGround.h""
#include"level\Level.h"
#include"Player2D.h"

BackGround::BackGround()
{
}


BackGround::~BackGround()
{
}

bool BackGround::Start() {
	//cmo�t�@�C���̓ǂݍ��݁B
	m_skinModel.Init(L"Assets/modelData/stage_one.cmo");
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

	m_texture.CreateFromDDSTextureFromFile(L"Assets/sprite/title.dds");
	m_sprite.Init(m_texture, 50,70 );
	
	m_SpritePos = { 10.0f,26.0f,20.0f };
	//���x���Ŏ擾
	Level level;
	level.Init(L"Assets/level/GhostSample.tkl", [&](LevelObjectData& objData) {
		if (objData.EqualObjectName(L"Box001")) {
			//�{�b�N�X�`��̃S�[�X�g���쐬����B
			PhysicsGhostObject* newGhost = new PhysicsGhostObject;
			m_GhostPos = objData.position;
			newGhost->CreateBox(
				objData.position,	//�������͍��W�B
				objData.rotation,	//�������͉�]�N�H�[�^�j�I���B
				objData.scale		//��O�����̓{�b�N�X�̃T�C�Y�B
			);
			m_ghotsObjects.push_back(newGhost);
			return true;
		}
	});
	return true;
}
bool BackGround::IsHit(CharacterController& charaCon)
{
	bool result = false;
	//�L�����N�^�[�R���g���[���[���S�[�X�g�ƏՓ˂��Ă��邩����B
	PhysicsWorld().ContactTest(charaCon, [&](const btCollisionObject& contactCollision) {
		for (int i = 0; i < (int)m_ghotsObjects.size(); ++i) {
			if (m_ghotsObjects[i]->IsSelf(contactCollision) == true) {
				//�Ԃ������A
				result = true;
				//�S�[�X�g�̉�]���擾
				m_GhostRot = m_ghotsObjects[i]->GetRotation();
				//�S�[�X�g�̍��W���擾
				m_GhostPos = m_ghotsObjects[i]->GetPosition();
				
				//�N�H�[�^�j�I������s����쐬�B
				CMatrix mRot;
				mRot.MakeRotationFromQuaternion(m_GhostRot);
				//1�s�ڂ���A�S�[�X�g���W�n��X�������������Ă���B
				//CVector3 xInGhost;
				m_xInGhost.x = mRot.m[0][0];
				m_xInGhost.y = mRot.m[0][1];
				m_xInGhost.z = mRot.m[0][2];
				//z��
				m_zInGhost.x = mRot.m[2][0];
				m_zInGhost.y = mRot.m[2][1];
				m_zInGhost.z = mRot.m[2][2];
				m_GhostRot.SetRotation(mRot);
			}
		}
	});
	return result;
}
void BackGround::Update() {
	//���[���h�s��̍X�V�B
	m_sprite.Update(m_SpritePos, CQuaternion::Identity(), CVector3::One(), { 0.5,0.0 });
	m_skinModel.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), m_Scale);

}

void BackGround::Render() {
	m_skinModel.QueryMaterials([&](SkinModelEffect* material) {
		if(material->EqualMaterialName(L"2DStage")) {
			m_skinModel.SetIsUV(true);
			material->SetAlbedoTexture(m_sprite.GetTex()->GetBody()/*m_texture.GetBody()*/);
		};
	});
	m_skinModel.Draw(
		MainCamera().GetViewMatrix(),
		MainCamera().GetProjectionMatrix(),
		enRenderMode_Normal
	);
}
void BackGround::PostRender() {
	
}