#pragma once
class Player;
class BackGround;
class GameCamera2D;
class Player2D :public GameObject
{
public:
	Player2D();
	~Player2D();
	bool Start()override;
	void Update()override;
	//void Render()override;
	void PostRender()override;
	//positionを取得
	CVector3 GetPosition() {
		return m_Pos;
	}
	void SetPosition(CVector3 pos) {
		m_Pos = pos;
	}
private:
	enum state2D {
		enidle_left = 0, 
		enidle_right,
		enwalk_leftL,
		enwalk_leftR,
		enwalk_rightL,
		enwalk_rightR,
	};
	state2D m_state;
	CShaderResourceView m_texture[6];				//テクスチャ
	CSprite m_sprite[6];							//スプライト
	CVector3 m_Pos;
	Player*m_player = nullptr;
	BackGround*m_background = nullptr;
	GameCamera2D*m_gamecamera2D = nullptr;
};

