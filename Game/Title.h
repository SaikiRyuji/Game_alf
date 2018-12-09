#pragma once
class Fade;
class Title:public GameObject
{
public:
	Title();
	~Title();
	bool Start()override;
	void Update()override;
	void Render()override;
private:
	bool m_isWaitFadeout = false;
	Fade*m_fade = nullptr;
	CShaderResourceView m_texture;
	CSprite m_sprite;
};

