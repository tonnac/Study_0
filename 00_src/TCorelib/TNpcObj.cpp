#include "TNpcObj.h"

bool TNpcObj::Frame()
{
	int iHalfX = m_rtDraw.right / 2;
	int iHalfY = m_rtDraw.bottom / 2;
	if ((m_pos.x+iHalfX) > g_rtClient.right)
	{
		m_fDir[0] *= -1.0f;
		m_pos.x = g_rtClient.right-iHalfX;
	}
	if (m_pos.y+iHalfY > g_rtClient.bottom)
	{
		m_fDir[1] *= -1.0f;
		m_pos.y = g_rtClient.bottom-iHalfY;
	}
	if ( (m_pos.x - iHalfX) < g_rtClient.left )
	{
		m_fDir[0] *= -1.0f;
		m_pos.x = g_rtClient.left + iHalfX;
	}
	if (m_pos.y - iHalfY < g_rtClient.top)
	{
		m_fDir[1] *= -1.0f;
		m_pos.y = g_rtClient.top+ iHalfY;
	}
	m_pos.x += m_fDir[0] * m_fSpeed * g_fSecPerFrame;
	m_pos.y += m_fDir[1] * m_fSpeed * g_fSecPerFrame;
	m_posDraw.x = m_pos.x - iHalfX;
	m_posDraw.y = m_pos.y - iHalfY;

	m_rtCollision.left = m_posDraw.x;
	m_rtCollision.top = m_posDraw.y;
	m_rtCollision.right = m_rtCollision.left + m_rtDraw.right;
	m_rtCollision.bottom = m_rtCollision.top + m_rtDraw.bottom;

	return true;
}

TNpcObj::TNpcObj()
{
	m_fSpeed = 50.0f + rand() % 150;
}


TNpcObj::~TNpcObj()
{
}
