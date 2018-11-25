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
		enState_FadeIn, //�t�F�[�h�C����
		enState_InGame, //�C���Q�[����
	};
	EnState m_state;
	Fade*m_fade=nullptr;
	float m_waitTimer;
	ID3D11DepthStencilState* m_depthStencilState;
};

