#pragma once
class Star:public GameObject
{
public:
	Star();
	~Star();
	bool Start(CVector3 pos, CQuaternion rot);
	void Update()override;
	//•`‰æˆ—
	void Render() override;
	//ƒ‚ƒfƒ‹À•W‚ğæ“¾
	CVector3 GetPosition() {
		return m_position;
	}
	void SetPosition(CVector3 pos) {
		m_position = pos;
	}
private:
	SkinModel m_model;
	CVector3 m_position;
	CQuaternion m_rotation;
};

