/*!
* @brief	定数バッファ。
*/
#pragma once
#include"GPUBuffer.h"
class CConstantBuffer:public CGPUBuffer
{
public:
	CConstantBuffer();
	~CConstantBuffer();
	/*!
	*@brief ConstantBufferを作成。
	*@param[in]	pInitData		初期データ。
	*@param[in]	bufferSize		バッファサイズ。
	*/
	bool Create(const void* pInitData, int bufferSize);
};