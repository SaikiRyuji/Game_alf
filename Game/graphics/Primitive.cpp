/*!
*@brief	�v���~�e�B�u�B
*/

#include "stdafx.h"
#include "graphics/Primitive.h"

	CPrimitive::CPrimitive()
	{
	}
	CPrimitive::~CPrimitive()
	{
		Release();
	}
	void CPrimitive::Release()
	{
		m_vertexBuffer.Release();
		m_indexBuffer.Release();
	}
	bool CPrimitive::Create(
		D3D_PRIMITIVE_TOPOLOGY topology,
		int numVertex,
		int vertexStride,
		void* pSrcVertexBuffer,
		int numIndex,
		CIndexBuffer::EnIndexType indexType,
		void* pSrcIndexBuffer)
	{
		Release();
		m_topology = topology;
		bool result = m_vertexBuffer.Create(numVertex, vertexStride, pSrcVertexBuffer);
		if (!result) {
			TK_WARNING("�v���~�e�B�u�̍쐬�Ɏ��s���܂����B");
			return false;
		}
		result = m_indexBuffer.Create(numIndex, indexType, pSrcIndexBuffer);
		if (!result) {
			TK_WARNING("�v���~�e�B�u�̍쐬�Ɏ��s���܂����B");
			return false;
		}

		return true;
	}
	void CPrimitive::Draw()
	{
		auto deviceContext = GfxEngine().GetD3DDeviceContext();
		UINT offset = 0;
		UINT stride = m_vertexBuffer.GetStride();
		deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer.GetBody(), &stride, &offset);
		
		CIndexBuffer::EnIndexType type = m_indexBuffer.GetIndexType();
		deviceContext->IASetIndexBuffer(
			m_indexBuffer.GetBody(),
			type == CIndexBuffer::enIndexType_16 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT,
			0
		);
		//�v���~�e�B�u�̃g�|���W�[��ݒ�B
		deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		//�`��B
		deviceContext->DrawIndexed(m_indexBuffer.GetNumIndex(), 0, 0);

	}
	void CPrimitive::Draw(ID3D11DeviceContext*rc,int numVertex)
	{
		UINT offset = 0;
		UINT stride = m_vertexBuffer.GetStride();
		rc->IASetVertexBuffers(
			0,
			1,
			&m_vertexBuffer.GetBody(),
			&stride,
			&offset
		);
		//�v���~�e�B�u�̃g�|���W�[��ݒ�B
		rc->IASetPrimitiveTopology(m_topology);
		//�`��B
		rc->Draw(numVertex, 0);
	}