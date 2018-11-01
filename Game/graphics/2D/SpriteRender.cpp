#include "stdafx.h"
#include "SpriteRender.h"


CSpriteRender::CSpriteRender()
{
}


CSpriteRender::~CSpriteRender()
{
}
void CSpriteRender::Init(const wchar_t* texFilePath, float w, float h, bool isDraw3D)
{
	m_isDraw3D = isDraw3D;
	m_texture.CreateFromDDSTextureFromFile(texFilePath);
	m_sprite.Init(m_texture, w, h);
}

void CSpriteRender::Update()
{
	m_sprite.SetTexture(m_texture);
	m_sprite.Update(m_position, m_rotation, m_scale, m_pivot);
}
void CSpriteRender::Draw()
{
	if (m_isDraw3D == true) {
		//m_sprite.Draw( rc,MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	}
}
void CSpriteRender::PostDraw()
{
	if (m_isDraw3D == false) {
		//m_sprite.Draw(rc,MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	}
}