#include "stdafx.h"
#include "GameObjectManager.h"

void GameObjectManager::Execute() {

	//�Q�[���I�u�W�F�N�g�̍폜
	ExecuteDeleteGameObjects();

	//StartWrapper�֐����Ă�
	for (GameObjectList objList : m_gameObjectListArray) {
		for (GameObject* obj : objList) {
			obj->StartWrapper();
		}
	}
	//UpdateWrapper�֐����Ă�
	for (GameObjectList objList : m_gameObjectListArray) {
		for (GameObject* obj : objList) {
			obj->UpdateWrapper();
		}
	}
	//RenderWrapper�֐����Ă�
	for (GameObjectList objList : m_gameObjectListArray) {
		for (GameObject* obj : objList) {
			obj->RenderWrapper();
		}
	}
	PhysicsWorld().DebubDrawWorld();
	//PostRenderWrapper�֐����Ă�
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
	//�o�b�t�@��؂�ւ��B
	m_currentDeleteObjectBufferNo = 1 ^ m_currentDeleteObjectBufferNo;
	for (GameObjectList& goList : m_deleteObjectArray[preBufferNo]) {
		for (GameObject* go : goList) {
			GameObjectPrio prio = go->GetPriority();
			GameObjectList& goExecList = m_gameObjectListArray.at(prio);
			auto it = std::find(goExecList.begin(), goExecList.end(), go);
			if (it != goExecList.end()) {
				//�폜���X�g���珜�O���ꂽ�B
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