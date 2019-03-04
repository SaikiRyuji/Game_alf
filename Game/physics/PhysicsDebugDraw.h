/*!
* @brief	コリジョンなどのデバッグ表示処理。
*/

#pragma once
#include <array> 
#include"../graphics/Shader.h"
#include"../graphics/Primitive.h"
#include"../math/Vector.h"
#include"../math/Matrix.h"
#include"../graphics/GPUBuffer/Constantbuffer.h"

class PhysicsDebugDraw : public btIDebugDraw {
	struct SConstantBuffer {
		CMatrix mView;
		CMatrix mProj;
	};
	int m_debugMode = btIDebugDraw::DBG_NoDebug;
	CPrimitive m_primitive;
	Shader m_vs;	//頂点シェーダー。
	Shader m_ps;	//ピクセルシェーダー。
	CConstantBuffer m_cb;
	static const int VERTEX_MAX = 1000000;
	std::array<CVector4, VERTEX_MAX> m_vertexBuffer;

	int m_numLine = 0;
public:
	void Init();

	void BeginDraw()
	{
		m_numLine = 0;
	}

	void EndDraw();
	void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;
	void drawContactPoint(const btVector3&, const btVector3&, btScalar, int, const btVector3&) override
	{
	}
	void reportErrorWarning(const char*) override
	{
	}
	void draw3dText(const btVector3&, const char*) override
	{
	}
	void setDebugMode(int debugMode) override
	{
		m_debugMode = debugMode;
	}
	int	getDebugMode() const override
	{
		return m_debugMode;
	}
};