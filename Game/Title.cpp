#include "stdafx.h"
#include "Title.h"
#include "Fade.h"
#include"Game.h"
Title::Title()
{
}


Title::~Title()
{
}
bool Title::Start() {
	m_texture.CreateFromDDSTextureFromFile(L"Assets/sprite/title.dds");
	m_sprite.Init(m_texture, 1280, 720);
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	return true;
}

void Title::Update() {
	if (m_isWaitFadeout) {
		if (!m_fade->IsFade()) {
			NewGO<Game>(0, "Game");
			DeleteGO(this);
		}
	}
	else {
		if (g_pad->IsTrigger(enButtonStart)) {
			m_isWaitFadeout = true;
			m_fade->StartFadeOut();
		}
	}
}
void Title::Render() {
	m_sprite.Draw(
		MainCamera2D().GetViewMatrix(),
		MainCamera2D().GetProjectionMatrix()
	);
}