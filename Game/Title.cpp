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