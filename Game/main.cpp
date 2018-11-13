#include "stdafx.h"
#include"EngineStruct.h"
#include "system/system.h"
#include "Player.h"
#include"BackGround.h"
#include"Enemy.h"
#include"GameCamera.h"
#include "level/Level.h"
#include"GameCamera.h"
#include"Engine.h"
#include"Fade.h"
#include"Title.h"

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	SInitParam initParam;
	initParam.hInstance = hInstance;
	initParam.nCmdShow = nCmdShow;
	initParam.screenWidth = 1280;
	initParam.screenHeight = 720;
	initParam.frameBufferWidth = 1280;
	initParam.frameBufferHeight = 720;
	
	//�Q�[�����[�v�B
	if (Engine().Init(initParam) == true) {
		//����
		NewGO<Fade>(1, "Fade");
		NewGO<Title>(0, nullptr);
		////�v���C��-

	/*	Player* player = nullptr;
		player = NewGO<Player>(0, "Player");

		BackGround* background = nullptr;
		background = NewGO<BackGround>(0, "background");

		CGameCamera* Camera = nullptr;
		Camera = NewGO<CGameCamera>(0, "Camera");

		Enemy*enemy = nullptr;
		enemy = NewGO<Enemy>(0, "Enemy");*/
		//�����܂�

		Engine().GameLoop();
	}
};