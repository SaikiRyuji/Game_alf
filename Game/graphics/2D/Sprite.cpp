#include "stdafx.h"
#include "Sprite.h"

struct SSimpleVertex {
			CVector4 pos;
			CVector2 tex;
		};

const CVector2	CSprite::DEFAULT_PIVOT = { 0.5f, 0.5f };
CSprite::CSprite()
{
}
CSprite::~CSprite()
{
}
void CSprite::Init(CShaderResourceView& tex, float w, float h)
{
	//シェーダーロード。
	m_ps.Load("Assets/shader/sprite.fx", "PSMain", Shader::EnType::PS);
	m_vs.Load("Assets/shader/sprite.fx", "VSMain", Shader::EnType::VS);
	m_size.x = w;
	m_size.y = h;
	float halfW = w * 0.5f;
	float halfH = h * 0.5f;
	//頂点バッファのソースデータ。
	SSimpleVertex vertices[] =
	{
		{
			CVector4(-halfW, -halfH, 0.0f, 1.0f),
			CVector2(0.0f, 1.0f),
		},
		{
			CVector4(halfW, -halfH, 0.0f, 1.0f),
			CVector2(1.0f, 1.0f),
		},
		{
			CVector4(-halfW, halfH, 0.0f, 1.0f),
			CVector2(0.0f, 0.0f)
		},
		{
			CVector4(halfW, halfH, 0.0f, 1.0f),
			CVector2(1.0f, 0.0f)
		}

	};
	short indices[] = { 0,1,2,3 };
		
	m_primitive.Create(
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
		4,
		sizeof(SSimpleVertex),
		vertices,
		4,
		CIndexBuffer::enIndexType_16,
		indices
	);
	m_textureSRV = &tex;
	m_cb.Create(nullptr, sizeof(SSpriteCB));
}
/*!
*@brief	更新
*@param[in]	trans		平行移動。
*@param[in]	rot			回転。
*@param[in]	scale		拡大。
*/
void CSprite::Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, const CVector2& pivot)
{
	//ピボットを考慮に入れた平行移動行列を作成。
	//ピボットは真ん中が0.0, 0.0、左上が-1.0f, -1.0、右下が1.0、1.0になるようにする。
	CVector2 localPivot = pivot;
	localPivot.x -= 0.5f;
	localPivot.y -= 0.5f;
	localPivot.x *= -2.0f;
	localPivot.y *= -2.0f;
	//画像のハーフサイズを求める。
	CVector2 halfSize = m_size;
	halfSize.x *= 0.5f;
	halfSize.y *= 0.5f;
	CMatrix mPivotTrans;

	mPivotTrans.MakeTranslation(
	{ halfSize.x * localPivot.x, halfSize.y * localPivot.y, 0.0f }
	);
	CMatrix mTrans, mRot, mScale;
	mTrans.MakeTranslation(trans);
	mRot.MakeRotationFromQuaternion(rot);
	mScale.MakeScaling(scale);
	m_world.Mul(mPivotTrans, mScale);
	m_world.Mul(m_world, mRot);
	m_world.Mul(m_world, mTrans);

}
void CSprite::Draw( const CMatrix& viewMatrix, const CMatrix& projMatrix)
{
	if (m_textureSRV == nullptr) {
		TK_WARNING("m_textureSRV is nullptr");
		return;
	}
	SSpriteCB cb;
	cb.WVP = m_world;
	cb.WVP.Mul(cb.WVP, viewMatrix);
	cb.WVP.Mul(cb.WVP, projMatrix);
	cb.mulColor = m_mulColor;
	auto deviceContext = GfxEngine().GetD3DDeviceContext();
	//定数バッファを更新。
	deviceContext->UpdateSubresource(m_cb.GetBody(), 0, nullptr, &cb, 0, 0);
	deviceContext->VSSetConstantBuffers(0, 1, &m_cb.GetBody());
	deviceContext->PSSetConstantBuffers(0, 1, &m_cb.GetBody());
	deviceContext->PSSetShaderResources(0, 1, &m_textureSRV->GetBody());
	deviceContext->PSSetShader((ID3D11PixelShader*)m_ps.GetBody(), NULL, 0);
	deviceContext->VSSetShader((ID3D11VertexShader*)m_vs.GetBody(), NULL, 0);
	deviceContext->IASetInputLayout(m_vs.GetInputLayout());
	m_primitive.Draw();
}