#include "stdafx.h"
#include "Star.h"


Star::Star()
{
}


Star::~Star()
{
}

bool Star::Start(CVector3 pos, CQuaternion rot) {
	m_position = pos;
	m_rotation = rot;
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/Star.cmo");
	return true;
};

void Star::Update() {

	CQuaternion Rot;
	Rot.SetRotationDeg(CVector3::AxisY(), 2.0f);
	m_rotation.Multiply(Rot);
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
}

void Star::Render() {
	m_model.Draw(
		MainCamera().GetViewMatrix(),
		MainCamera().GetProjectionMatrix(),
		enRenderMode_Normal
	);
}