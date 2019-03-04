/*!
* @brief	�S�[�X�g�I�u�W�F�N�g�B
*/
#pragma once
#include"PhysicsObjectBase.h"
/*!
* @brief	�S�[�X�g�I�u�W�F�N�g
*@detail
* �S�[�X�g�I�u�W�F�N�g�͍��̂����蔲���邠���蔻��̃I�u�W�F�N�g�ł��B
* �L�����N�^�[�̃`�F�b�N�|�C���g�ʉߔ���A�N���A����Ȃǂ�
* �L�����N�^�[�����蔲����K�v�̂��邠���蔻��Ɏg���܂��B
*/
class PhysicsGhostObject:public PhysicsObjectBase
{
public:
	PhysicsGhostObject();
	~PhysicsGhostObject() {
		Release();
	};
	/*!
	* @brief	�S�[�X�g�I�u�W�F�N�g������B
	*@detail
	* �����I�ȃ^�C�~���O�ŃS�[�X�g�I�u�W�F�N�g���폜�������ꍇ�ɌĂяo���Ă��������B
	*/
	void Release();
	/*!
	* @brief	�����œn���ꂽ�S�[�X�g�I�u�W�F�N�g���������g���ǂ�������B
	*/
	bool IsSelf(const btCollisionObject& ghost) const
	{
		return &ghost == &m_ghostObject;
	}
	btGhostObject GetSelf() {
		return m_ghostObject;
	}
	/*!
	* @brief	���W��ݒ�B
	*/
	void SetPosition(const CVector3& pos)
	{
		auto& btTrans = m_ghostObject.getWorldTransform();
		btVector3 btPos;
		pos.CopyTo(btPos);
		btTrans.setOrigin(btPos);
	}
	//���W���擾
	CVector3 GetPosition() {
		return m_pos;
	}
	/*!
	* @brief	��]��ݒ�B
	*/
	void SetRotation(const CQuaternion& rot)
	{
		auto& btTrans = m_ghostObject.getWorldTransform();
		btQuaternion btRot;
		rot.CopyTo(btRot);
		btTrans.setRotation(btRot);
	}
	//��]���擾
	CQuaternion GetRotation() {
		return m_rot;
	}
private:
	/*!
	* @brief	�S�[�X�g�쐬�����̋��ʏ����B
	*/
	void CreateCommon(CVector3 pos, CQuaternion rot);
private:
	bool						m_isRegistPhysicsWorld = false;	//!<�������[���h�ɓo�^���Ă��邩�ǂ����̃t���O�B
	btGhostObject				m_ghostObject;	//!<�S�[�X�g
	CQuaternion					m_rot = CQuaternion::Identity();
	CVector3					m_pos = CVector3::Zero();
};

