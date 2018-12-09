#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include"BackGround.h"
#include"Enemy.h"
#include"GameCamera.h"
#include"Fade.h"
#include"Star.h"

Game::Game()
{
}


Game::~Game()
{
}

bool Game::Start() {

	m_fade = FindGO<Fade>("Fade");
	//スターレベル作成
	m_level.Init(L"Assets/level/StarL.tkl", [&](LevelObjectData& objData) {
		if (wcscmp(objData.name, L"Star") == 0) {
			auto star = NewGO<Star>(0, "star");
			m_starList.push_back(star);
			star->Start(objData.position, objData.rotation);
			return true;
		}
	});

	BackGround* background = nullptr;
	background = NewGO<BackGround>(0, "background");
	//プレイヤ-
	Player* player = nullptr;
	player = NewGO<Player>(0, "Player");

	CGameCamera* Camera = nullptr;
	Camera = NewGO<CGameCamera>(0, "Camera");

	Enemy*enemy = nullptr;
	enemy = NewGO<Enemy>(0, "Enemy");
	m_fade = FindGO<Fade>("Fade");
	m_fade->StartFadeIn();
	m_state = enState_FadeIn;
	return true;
}

void Game::Update() {
	switch (m_state) {
	case enState_FadeIn:
		//GraphicsEngine().GetTonemap().Reset();
		if (!m_fade->IsFade()) {
			m_state = enState_InGame;
		}
		break;
	case enState_InGame: {
		m_waitTimer += GameTime().GetFrameDeltaTime();
		if (m_waitTimer < 0.1f) {
			//ゲームが開始して0.1秒経過するまでトーンマップの明暗順応はしない
			//GraphicsEngine().GetTonemap().Reset();
		}
	}
						 break;
	}

	/*if (g_pad->IsTrigger(enButtonStart)){ 
		m_fade->StartFadeOut();
	}*/
}

void Game::Render() {
}