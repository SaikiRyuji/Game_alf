#include "stdafx.h"
#include "GameObjectManager.h"

void GameObjectManager::Execute() {

	//ゲームオブジェクトの削除
	ExecuteDeleteGameObjects();

	//StartWrapper関数を呼ぶ
	for (GameObjectList objList : m_gameObjectListArray) {
		for (GameObject* obj : objList) {
			obj->StartWrapper();
		}
	}
	//UpdateWrapper関数を呼ぶ
	for (GameObjectList objList : m_gameObjectListArray) {
		for (GameObject* obj : objList) {
			obj->UpdateWrapper();
		}
	}
	//RenderWrapper関数を呼ぶ
	for (GameObjectList objList : m_gameObjectListArray) {
		for (GameObject* obj : objList) {
			obj->RenderWrapper();
		}
	}
	PhysicsWorld().DebubDrawWorld();
	//PostRenderWrapper関数を呼ぶ
	for (GameObjectList objList : m_gameObjectListArray) {
		for (GameObject* obj : objList) {
			obj->PostRenderWrapper();
		}
	}
}
void GameObjectManager::Init(int gameObjectPrioMax)
{
	m_gameObjectPriorityMax = static_cast<GameObjectPrio>(gameObjectPrioMax);
	m_gameObjectListArray.resize(gameObjectPrioMax);
	m_deleteObjectArray[0].resize(gameObjectPrioMax);
	m_deleteObjectArray[1].resize(gameObjectPrioMax);
}
void GameObjectManager::ExecuteDeleteGameObjects() {
	
	int preBufferNo = m_currentDeleteObjectBufferNo;
	//バッファを切り替え。
	m_currentDeleteObjectBufferNo = 1 ^ m_currentDeleteObjectBufferNo;
	for (GameObjectList& goList : m_deleteObjectArray[preBufferNo]) {
		for (GameObject* go : goList) {
			GameObjectPrio prio = go->GetPriority();
			GameObjectList& goExecList = m_gameObjectListArray.at(prio);
			auto it = std::find(goExecList.begin(), goExecList.end(), go);
			if (it != goExecList.end()) {
				//削除リストから除外された。
				(*it)->m_isRegistDeadList = false;
				if ((*it)->IsNewFromGameObjectManager()) {
					delete (*it);
				}
			}
			goExecList.erase(it);
		}
		goList.clear();
	}
}