#pragma once
class Fade;
class Title:public GameObject
{
public:
	Title();
	~Title();
	bool Start()override;
	void Update()override;
private:
	bool m_isWaitFadeout = false;
	Fade*m_fade = nullptr;
};

