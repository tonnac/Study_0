#include "Button.h"

bool Button::Init()
{
	return true;
}
bool Button::Frame()
{
	m_rtCollision.left = m_posDraw.x;
	m_rtCollision.top = m_posDraw.y;
	m_rtCollision.right = m_rtCollision.left + m_rtDraw.right;
	m_rtCollision.bottom = m_rtCollision.top + m_rtDraw.bottom;
	return true;
}
//bool Button::Render()
//{
//	return true;
//}
bool Button::Release()
{
	return true;
}

Button::Button()
{
}


Button::~Button()
{
}
