#include "NPCObj.h"


bool NPCObj::Frame()
{
	int iHalfX = m_rtDraw.right / 2;
	int iHalfY = m_rtDraw.bottom / 2;
	if (m_pos.x + iHalfX > g_rtClient.right)
	{
		m_fDir[0] *= -1.0f;
		m_pos.x = g_rtClient.right - iHalfX;
	}
	if (m_pos.y + iHalfY > g_rtClient.bottom)
	{
		m_fDir[1] *= -1.0f;
		m_pos.y = g_rtClient.bottom - iHalfY;
	}
	if (m_pos.x - iHalfX < g_rtClient.left)
	{
		m_fDir[0] *= -1.0f;
		m_pos.x = g_rtClient.left + iHalfX;
	}
	if (m_pos.y - iHalfY < g_rtClient.top)
	{
		m_fDir[1] *= -1.0f;
		m_pos.y = g_rtClient.top + iHalfY;
	}
	m_posDraw.x += m_fDir[0] * m_fSpeed * g_fSecPerFrame;
	m_posDraw.y += m_fDir[1] * m_fSpeed * g_fSecPerFrame;
	m_posDraw.x = m_pos.x - (m_rtDraw.right / 2);
	m_posDraw.y = m_pos.y - (m_rtDraw.bottom / 2);
	return true;
}


NPCObj::NPCObj()
{
	m_fSpeed = 100.0f;
}


NPCObj::~NPCObj()
{
}
