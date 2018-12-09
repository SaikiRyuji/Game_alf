#pragma once
class Star:public GameObject
{
public:
	Star();
	~Star();
	bool Start(CVector3 pos, CQuaternion rot);
	void Update()override;
	//�`�揈��
	void Render() override;
	//���f�����W���擾
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

