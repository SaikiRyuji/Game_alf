#pragma once
#include"level\Level.h"
class Fade;
class Star;
class Game:public GameObject
{
public:
	Game();
	~Game();
	bool Start()override;
	void Update()override;
	void Render()override;
private:
	enum EnState {
		enState_FadeIn, //�t�F�[�h�C����
		enState_InGame, //�C���Q�[����
	};
	EnState m_state;
	Fade*m_fade=nullptr;
	float m_waitTimer;
	Level m_level;
	std::vector< Star* > m_starList;		//�G�l�~�[�̃��X�g�B
	ID3D11DepthStencilState* m_depthStencilState;
};

