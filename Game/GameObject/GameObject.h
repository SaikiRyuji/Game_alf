#pragma once
class GameObjectManager;
typedef unsigned char	GameObjectPrio;
class GameObject :Noncopyable
{
public:
	GameObject() :
		m_priority(0),
		m_isStart(false),
		m_isDead(false),
		m_isNewFromGameObjectManager(false)
	{
	}
	virtual bool Start() { return true; }
	/*!
	*@brief	�X�V
	*/
	virtual void Update() {}
	/*!
	*@brief	�`��
	*/
	virtual void Draw()
	{
	}
	/*!
	*@brief	Render�֐������s���ꂽ��ŌĂ΂��`�揈��
	*@details
	* �|�X�g�G�t�F�N�g�̌�Ŏ��s����܂��BHUD�Ȃǃ|�X�g�G�t�F�N�g�̉e�����󂯂����Ȃ��`�敨�͂����Ń����_�����O���Ă��������B
	*/
	virtual void PostDraw() {
	}
	/*!
	*@brief	�C���X�^���X���������ꂽ����ɌĂ΂��֐��B
	*@details	�R���X�g���N�^���Ă΂ꂽ��ő��Ă΂�܂��B
	*/
	virtual void Awake() {}
	/*!
	*@brief	�폜�����Ƃ��ɌĂ΂��B
	*@details	CGameManager::DeleteGameObject���Ă񂾂Ƃ��Ɏ��s����܂��B
	* �f�X�g���N�^���O�Ɏ��s����܂��B
	*/
	virtual void OnDestroy() {}

	/*!
	*@brief	���s�D��x���擾�B
	*/
	GameObjectPrio GetPriority() const
	{
		return m_priority;
	}
	/*!
	*@brief	���S�t���O�𗧂Ă�B
	*@details
	*/
	void SetDeadMark()
	{
		m_isDead = true;
	}


	void SetMarkNewFromGameObjectManager()
	{
		m_isNewFromGameObjectManager = true;
	}
	bool IsNewFromGameObjectManager() const
	{
		return m_isNewFromGameObjectManager;
	}
	//Start�֐�
	void StartWrapper()
	{
		if (m_isActive && !m_isStart && !m_isDead && !m_isRegistDeadList) {
			if (Start()) {
				//���������������B
				m_isStart = true;
			}
		}
	}
	//Update�֐����Ă�
	void UpdateWrapper()
	{
		if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList) {
			Update();
		}
	}
	//Draw�֐����Ă�
	void DrawWrapper()
	{
		if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList) {
			Draw();
		}
	}
	void PostDrawWrapper()
	{
		if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList) {
			PostDraw();
		}
	}
	friend class GameObjectManager;
protected:
	GameObjectPrio	m_priority;			//!<���s�D��x�B
	bool m_isStart;						//!<Start�̊J�n�t���O�B
	bool m_isDead;						//!<���S�t���O�B
	bool m_isRegistDeadList = false;	//!<���S���X�g�ɐς܂�Ă���B
	bool m_isNewFromGameObjectManager;	//!<GameObjectManager��new���ꂽ�B
	bool m_isRegist = false;			//!<GameObjectManager�ɓo�^����Ă���H
	bool m_isActive = true;				//!<Active�t���O�B
	unsigned int m_tags = 0;			//!<�^�O�B
	unsigned int m_nameKey = 0;			//!<���O�L�[�B
};

