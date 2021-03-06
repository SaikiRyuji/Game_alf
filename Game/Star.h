#pragma once
class Star:public GameObject
{
public:
	Star();
	~Star();
	bool Start(CVector3 pos, CQuaternion rot);
	void Update()override;
	//描画処理
	void Render() override;
	//モデル座標を取得
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

