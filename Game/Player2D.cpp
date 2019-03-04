#include "stdafx.h"
#include "Player2D.h"
#include"Player.h"
#include"BackGround.h"
#include"GameCamera2D.h"

Player2D::Player2D()
{
}


Player2D::~Player2D()
{
}

bool Player2D::Start() {
	//dds読み込み
	m_texture[enidle_left].CreateFromDDSTextureFromFile(L"Assets/sprite/dot/idle_left.dds");
	m_texture[enidle_right].CreateFromDDSTextureFromFile(L"Assets/sprite/dot/idle_right.dds");
	m_texture[enwalk_leftL].CreateFromDDSTextureFromFile(L"Assets/sprite/dot/walk_left1.dds");
	m_texture[enwalk_leftR].CreateFromDDSTextureFromFile(L"Assets/sprite/dot/walk_left2.dds");
	m_texture[enwalk_rightL].CreateFromDDSTextureFromFile(L"Assets/sprite/dot/walk_right1.dds");
	m_texture[enwalk_rightR].CreateFromDDSTextureFromFile(L"Assets/sprite/dot/walk_right2.dds");
	//スプライト初期化
	m_sprite[enidle_left].Init(m_texture[enidle_left],10.0,10.0);
	m_sprite[enidle_right].Init(m_texture[enidle_right], 10.0, 10.0);
	m_sprite[enwalk_leftL].Init(m_texture[enwalk_leftL], 10.0, 10.0);
	m_sprite[enwalk_leftR].Init(m_texture[enwalk_leftR], 10.0, 10.0);
	m_sprite[enwalk_rightL].Init(m_texture[enwalk_rightL], 10.0, 10.0);
	m_sprite[enwalk_rightR].Init(m_texture[enwalk_rightR], 10.0, 10.0);
	
	m_background = FindGO<BackGround>("background");
	m_state = enidle_right;
	m_Pos = m_background->GetGhostPos();
	m_player = FindGO<Player>("Player");
	
	return true;
}
void Player2D::Update() {
	if (m_player->Get2DFlag()) {
		if (g_pad->GetLStickXF()) {
			m_Pos = m_Pos+m_background->GetXInGhost()* 2.0*g_pad->GetLStickXF();
			
			//右移動
			if (0.0 < g_pad->GetLStickXF()) {
				if (m_state == enwalk_rightR) {
					m_state = enwalk_rightL;
				}
				else if (m_state == enwalk_rightL) {
					m_state = enidle_right;
				}
				else {
					m_state = enwalk_rightR;
				}
			}
			//左移動
			if (0.0 > g_pad->GetLStickXF()) {
				if (m_state == enwalk_leftR) {
					m_state = enwalk_leftL;
				}
				else if (m_state == enwalk_leftL) {
					m_state = enidle_left;
				}
				else {
					m_state = enwalk_leftR;
				}
			}
		}
		if (g_pad->IsTrigger(enButtonA)) {
			m_Pos.y += 5.0f;
		}
		
		m_player->GetCharaCon().SetPosition(m_Pos);
		m_player->GetCharaCon().Execute(GameTime().GetFrameDeltaTime(), CVector3::Zero());
		m_sprite[m_state].Update(m_Pos, m_background->GetGhostRotation(), CVector3::One(), { 0.5,0.0 });
		if (!(m_background->IsHit(m_player->GetCharaCon())) && m_player->Get2DFlag()) {
			m_gamecamera2D = FindGO<GameCamera2D>("Camera2D");
			CVector3 movespeed = m_background->GetZInGhost()*20.0f;
			movespeed.y += 100.0f;
			m_player->SetMoveSped(movespeed);
			m_player->Move();
			m_player->Set2DFlag(false);
			m_gamecamera2D->Notify3DGame();
		}
	}
}
void Player2D::PostRender() {
	if (m_player->Get2DFlag()) {
		m_sprite[m_state].Draw(
			MainCamera().GetViewMatrix(),
			MainCamera().GetProjectionMatrix()
		);
	}
}