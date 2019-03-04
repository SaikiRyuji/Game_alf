#pragma once
class GameClear : public GameObject
{
public:
	GameClear();
	~GameClear();
	bool Start() override;
	void Update() override;
};

