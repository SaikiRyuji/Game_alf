#pragma once
class Fade;
class Game:public GameObject
{
public:
	Game();
	~Game();
	bool Start()override;
	void Update()override;
	void Draw()override;
private:
	enum EnState {
		enState_FadeIn, //フェードイン中
		enState_InGame, //インゲーム中
	};
	EnState m_state;
	Fade*m_fade=nullptr;
	float m_waitTimer;
	ID3D11DepthStencilState* m_depthStencilState;
};

