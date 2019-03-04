/*!
* @brief	�R���W�����Ȃǂ̃f�o�b�O�\�������B
*/

#include "stdafx.h"
#include "PhysicsDebugDraw.h"


void PhysicsDebugDraw::Init()
{

	//���C���X�g���b�v�̃e�X�g�B
	m_primitive.Create(
		D3D_PRIMITIVE_TOPOLOGY_LINELIST,
		static_cast<int>(m_vertexBuffer.size()),
		sizeof(CVector4),
		&m_vertexBuffer[0],
		0,
		CIndexBuffer::enIndexType_32,
		nullptr
	);
	m_vs.Load("Assets/shader/linePrimitive.fx", "VSMain", Shader::EnType::VS);
	m_ps.Load("Assets/shader/linePrimitive.fx", "PSMain", Shader::EnType::PS);
	m_cb.Create(nullptr, sizeof(SConstantBuffer));
}
void PhysicsDebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	int baseIndex = m_numLine * 2;
	m_vertexBuffer[baseIndex].Set(CVector3(from.x(), from.y(), from.z()));
	m_vertexBuffer[baseIndex + 1].Set(CVector3(to.x(), to.y(), to.z()));
	m_numLine++;

}
void PhysicsDebugDraw::EndDraw()
{
	//�萔�o�b�t�@�̍X�V�B
	SConstantBuffer cb;
	cb.mView = MainCamera().GetViewMatrix();
	cb.mProj = MainCamera().GetProjectionMatrix();
	auto deviceContext = GfxEngine().GetD3DDeviceContext();
	deviceContext->UpdateSubresource(m_cb.GetBody(), 0, NULL, &cb, 0, 0);

	deviceContext->VSSetShader((ID3D11VertexShader*)m_vs.GetBody(), NULL, 0);
	deviceContext->PSSetShader((ID3D11PixelShader*)m_ps.GetBody(), NULL, 0);
	deviceContext->VSSetConstantBuffers(0,1,&m_cb.GetBody());
	//���̓��C�A�E�g��ݒ�B
	deviceContext->IASetInputLayout(m_vs.GetInputLayout());
	deviceContext->UpdateSubresource(m_primitive.GetVertexBuffer().GetBody(), 0, NULL, &m_vertexBuffer[0], 0, 0);
	m_primitive.Draw(deviceContext,m_numLine * 2);
}