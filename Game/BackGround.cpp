#include "stdafx.h"
#include "BackGround.h""


BackGround::BackGround()
{
}


BackGround::~BackGround()
{
}

bool BackGround::Start() {
	//cmoファイルの読み込み。
	m_skinModel.Init(L"Assets/modelData/stageMash1.cmo");
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
	return true;
}

void BackGround::Update() {
	//ワールド行列の更新。
	m_skinModel.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), m_Scale);

}

void BackGround::Draw() {
	m_skinModel.Draw(
		MainCamera().GetViewMatrix(),
		MainCamera().GetProjectionMatrix()
	);
}