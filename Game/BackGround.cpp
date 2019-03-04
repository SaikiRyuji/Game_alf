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
	//cmoファイルの読み込み。
	m_skinModel.Init(L"Assets/modelData/stage_one.cmo");
	//メッシュコライダーを作成。
	m_meshCollider.CreateFromSkinModel(m_skinModel, nullptr);
	//剛体の情報を作成。
	RigidBodyInfo rbInfo;
	rbInfo.pos = CVector3::Zero();
	rbInfo.rot = CQuaternion::Identity();
	rbInfo.collider = &m_meshCollider;
	rbInfo.mass = 0.0f;							//質量を0にすると動かない剛体になる。
												//背景などの動かないオブジェクトは0を設定するとよい。
	m_rigidBody.Create(rbInfo);					//作成した情報を使って剛体を作成する。
	PhysicsWorld().AddRigidBody(m_rigidBody);	//作成した剛体を物理ワールドに追加する。
	m_Scale = { 1.0,1.0,1.0 };

	m_texture.CreateFromDDSTextureFromFile(L"Assets/sprite/title.dds");
	m_sprite.Init(m_texture, 50,70 );
	
	m_SpritePos = { 10.0f,26.0f,20.0f };
	//レベルで取得
	Level level;
	level.Init(L"Assets/level/GhostSample.tkl", [&](LevelObjectData& objData) {
		if (objData.EqualObjectName(L"Box001")) {
			//ボックス形状のゴーストを作成する。
			PhysicsGhostObject* newGhost = new PhysicsGhostObject;
			m_GhostPos = objData.position;
			newGhost->CreateBox(
				objData.position,	//第一引数は座標。
				objData.rotation,	//第二引数は回転クォータニオン。
				objData.scale		//第三引数はボックスのサイズ。
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
	//キャラクターコントローラーがゴーストと衝突しているか判定。
	PhysicsWorld().ContactTest(charaCon, [&](const btCollisionObject& contactCollision) {
		for (int i = 0; i < (int)m_ghotsObjects.size(); ++i) {
			if (m_ghotsObjects[i]->IsSelf(contactCollision) == true) {
				//ぶつかった、
				result = true;
				//ゴーストの回転を取得
				m_GhostRot = m_ghotsObjects[i]->GetRotation();
				//ゴーストの座標を取得
				m_GhostPos = m_ghotsObjects[i]->GetPosition();
				
				//クォータニオンから行列を作成。
				CMatrix mRot;
				mRot.MakeRotationFromQuaternion(m_GhostRot);
				//1行目から、ゴースト座標系のX軸を引っ張ってくる。
				//CVector3 xInGhost;
				m_xInGhost.x = mRot.m[0][0];
				m_xInGhost.y = mRot.m[0][1];
				m_xInGhost.z = mRot.m[0][2];
				//z軸
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
	//ワールド行列の更新。
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