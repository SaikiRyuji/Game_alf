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
	*@brief	ゲームオブジェクトの削除を実行。
	*/
	void ExecuteDeleteGameObjects();
	//ゲームオブジェクトの名前キーを作成。
	static unsigned int MakeGameObjectNameKey(const char* objectName)
	{
		static const unsigned int defaultNameKey = Util::MakeHash("Undefined");	//名前キー。
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
	*@brief	インスタンスの取得。
	*/
	static GameObjectManager& Instance()
	{
		static GameObjectManager instance;
		return instance;
	}
	/*!
	*@brief	実行。
	*/
	void Execute();
	
	/*!
	*@brief	初期化。
	*/
	void Init(int gameObjectPrioMax);

	/*!
	*@brief	ゲームオブジェクトの生成。
	*/
	template<class T, class... TArgs>
	T* NewGameObject(GameObjectPrio prio, const char* objectName, TArgs... ctorArgs)
	{
		(void*)objectName;
		//インスタンス生成
		T* newObject = new T(ctorArgs...);
		newObject->Awake();
		newObject->SetMarkNewFromGameObjectManager();
		//優先度の要素にプッシュバック
		m_gameObjectListArray.at(prio).push_back(newObject);
		unsigned int hash = MakeGameObjectNameKey(objectName);
		newObject->m_isRegist = true;
		newObject->m_priority = prio;
		newObject->m_nameKey = hash;
		return newObject;
	}
	/*!
	*@brief	ゲームオブジェクトの削除。
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
	*@brief	ゲームオブジェクトの検索。
	*@details
	* 重い
	*@param[in]	objectName		オブジェクト名。
	*/
	template<class T>
	T* FindGameObject(const char* objectName)
	{
		//名前検索
		unsigned int nameKey = Util::MakeHash(objectName);
		for (auto goList : m_gameObjectListArray) {
			for (auto go : goList) {
				if (go->m_nameKey == nameKey) {
					//見つけた。
					return dynamic_cast<T*>(go);
				}
			}
		}
		//見つからなかった。
		return nullptr;
	}
private:
	Transform m_transform;
	typedef std::list<GameObject*>	GameObjectList;
	std::vector<GameObjectList>	m_gameObjectListArray;					//!<ゲームオブジェクトの優先度付きリスト。
	std::vector<GameObjectList>	m_deleteObjectArray[2];					//!<削除するオブジェクトのリスト。削除処理を行っている最中にDeleteGameObjectが呼ばれる可能性が高いので、ダブルバッファ化。
	std::list<Transform*>		m_childrenOfRootTransformList;			//!<ルートの子供のTransformのリスト。
	GameObjectPrio				m_gameObjectPriorityMax;				//!<ゲームオブジェクトの優先度の最大数。
	int m_currentDeleteObjectBufferNo = 0;								//!<現在の削除オブジェクトのバッファ番号。
	static const unsigned char 			GAME_OBJECT_PRIO_MAX = 255;		//!<ゲームオブジェクトの優先度の最大値。
};
static inline GameObjectManager& GOM()
{
	return GameObjectManager::Instance();
}
//ゲームオブジェクト作成のヘルパー関数
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
//ゲームオブジェクト削除のヘルパー関数
static inline void DeleteGO(GameObject* go)
{
	GOM().DeleteGameObject(go);
}
/*!
*@brief	ゲームオブジェクトの検索のヘルパー関数。
*@param[in]	objectName	ゲームオブジェクト名。
*/
template<class T>
static inline T* FindGO(const char* objectName)
{
	return GOM().FindGameObject<T>(objectName);
}