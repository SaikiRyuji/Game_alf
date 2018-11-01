#pragma once
#include"GameObject\GameObject.h"
#include"../util/Util.h"
#include"Transform.h"
class GameObjectManager :Noncopyable
{
private:
	GameObjectManager() :
		m_gameObjectPriorityMax(0) 
	{
	}
	~GameObjectManager()
	{
	}
	/*!
	*@brief	�Q�[���I�u�W�F�N�g�̍폜�����s�B
	*/
	void ExecuteDeleteGameObjects();
	//�Q�[���I�u�W�F�N�g�̖��O�L�[���쐬�B
	static unsigned int MakeGameObjectNameKey(const char* objectName)
	{
		static const unsigned int defaultNameKey = Util::MakeHash("Undefined");	//���O�L�[�B
		unsigned int hash;
		if (objectName == nullptr) {
			hash = defaultNameKey;
		}
		else {
			hash = Util::MakeHash(objectName);
		}
		return hash;
	}
public:
	/*!
	*@brief	�C���X�^���X�̎擾�B
	*/
	static GameObjectManager& Instance()
	{
		static GameObjectManager instance;
		return instance;
	}
	/*!
	*@brief	���s�B
	*/
	void Execute();
	
	/*!
	*@brief	�������B
	*/
	void Init(int gameObjectPrioMax);

	/*!
	*@brief	�Q�[���I�u�W�F�N�g�̐����B
	*/
	template<class T, class... TArgs>
	T* NewGameObject(GameObjectPrio prio, const char* objectName, TArgs... ctorArgs)
	{
		(void*)objectName;
		//�C���X�^���X����
		T* newObject = new T(ctorArgs...);
		newObject->Awake();
		newObject->SetMarkNewFromGameObjectManager();
		//�D��x�̗v�f�Ƀv�b�V���o�b�N
		m_gameObjectListArray.at(prio).push_back(newObject);
		unsigned int hash = MakeGameObjectNameKey(objectName);
		newObject->m_isRegist = true;
		newObject->m_priority = prio;
		newObject->m_nameKey = hash;
		return newObject;
	}
	/*!
	*@brief	�Q�[���I�u�W�F�N�g�̍폜�B
	*/
	void DeleteGameObject(GameObject* gameObject)
	{
		if (gameObject != nullptr
			&& gameObject->m_isRegist
			) {
			gameObject->SetDeadMark();
			gameObject->OnDestroy();
			gameObject->m_isRegist = false;
			gameObject->m_isRegistDeadList = true;

			m_deleteObjectArray[m_currentDeleteObjectBufferNo].at(gameObject->GetPriority()).push_back(gameObject);
			gameObject = nullptr;
		}
	}
	/*!
	*@brief	�Q�[���I�u�W�F�N�g�̌����B
	*@details
	* �d��
	*@param[in]	objectName		�I�u�W�F�N�g���B
	*/
	template<class T>
	T* FindGameObject(const char* objectName)
	{
		//���O����
		unsigned int nameKey = Util::MakeHash(objectName);
		for (auto goList : m_gameObjectListArray) {
			for (auto go : goList) {
				if (go->m_nameKey == nameKey) {
					//�������B
					return dynamic_cast<T*>(go);
				}
			}
		}
		//������Ȃ������B
		return nullptr;
	}
private:
	Transform m_transform;
	typedef std::list<GameObject*>	GameObjectList;
	std::vector<GameObjectList>	m_gameObjectListArray;					//!<�Q�[���I�u�W�F�N�g�̗D��x�t�����X�g�B
	std::vector<GameObjectList>	m_deleteObjectArray[2];					//!<�폜����I�u�W�F�N�g�̃��X�g�B�폜�������s���Ă���Œ���DeleteGameObject���Ă΂��\���������̂ŁA�_�u���o�b�t�@���B
	std::list<Transform*>		m_childrenOfRootTransformList;			//!<���[�g�̎q����Transform�̃��X�g�B
	GameObjectPrio				m_gameObjectPriorityMax;				//!<�Q�[���I�u�W�F�N�g�̗D��x�̍ő吔�B
	int m_currentDeleteObjectBufferNo = 0;								//!<���݂̍폜�I�u�W�F�N�g�̃o�b�t�@�ԍ��B
	static const unsigned char 			GAME_OBJECT_PRIO_MAX = 255;		//!<�Q�[���I�u�W�F�N�g�̗D��x�̍ő�l�B
};
static inline GameObjectManager& GOM()
{
	return GameObjectManager::Instance();
}
//�Q�[���I�u�W�F�N�g�쐬�̃w���p�[�֐�
template<class T, class... TArgs>
static inline T* NewGO(int priority, const char* objectName, TArgs... ctorArgs)
{
	return GOM().NewGameObject<T>((GameObjectPrio)priority, objectName, ctorArgs...);
}

template<class T>
static inline T* NewGO(int priority)
{
	return GOM().NewGameObject<T>((GameObjectPrio)priority, nullptr);
}
//�Q�[���I�u�W�F�N�g�폜�̃w���p�[�֐�
static inline void DeleteGO(GameObject* go)
{
	GOM().DeleteGameObject(go);
}
/*!
*@brief	�Q�[���I�u�W�F�N�g�̌����̃w���p�[�֐��B
*@param[in]	objectName	�Q�[���I�u�W�F�N�g���B
*/
template<class T>
static inline T* FindGO(const char* objectName)
{
	return GOM().FindGameObject<T>(objectName);
}