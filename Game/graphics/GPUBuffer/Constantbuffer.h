/*!
* @brief	�萔�o�b�t�@�B
*/
#pragma once
#include"GPUBuffer.h"
class CConstantBuffer:public CGPUBuffer
{
public:
	CConstantBuffer();
	~CConstantBuffer();
	/*!
	*@brief ConstantBuffer���쐬�B
	*@param[in]	pInitData		�����f�[�^�B
	*@param[in]	bufferSize		�o�b�t�@�T�C�Y�B
	*/
	bool Create(const void* pInitData, int bufferSize);
};