#include "stdafx.h"
#include "Fade.h"


Fade::Fade()
{
}


Fade::~Fade()
{
}

bool Fade::Start() {
	m_texture.CreateFromDDSTextureFromFile(L"Assets/sprite/fade.dds");
	m_sprite.Init(m_texture,1280,720);
	return true;
}

void Fade::Update()
{
	switch (m_state) {
	case enState_FadeIn:
		m_currentAlpha -= 2.0f * GameTime().GetFrameDeltaTime();
		if (m_currentAlpha <= 0.0f) {
			m_currentAlpha = 0.0f;
			m_state = enState_Idle;
		}
		break;
	case enState_FadeOut:
		m_currentAlpha += 2.0f * GameTime().GetFrameDeltaTime();
		if (m_currentAlpha >= 1.0f) {
			m_currentAlpha = 1.0f;
			m_state = enState_Idle;
		}
		break;
	case enState_Idle:
		break;
	}
	m_sprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
}
void Fade::PostDraw()
{
	if (m_currentAlpha > 0.0f) {
		m_sprite.SetMulColor({ 1.0f,1.0f,1.0f,m_currentAlpha });
		m_sprite.Draw(
			MainCamera2D().GetViewMatrix(),
			MainCamera2D().GetProjectionMatrix()
		);
	}
}