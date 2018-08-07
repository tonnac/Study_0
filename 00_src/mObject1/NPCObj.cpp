#include "NPCObj.h"


bool NPCObj::Frame()
{
	int iHalfX = m_rtDraw.right / 2;
	int iHalfY = m_rtDraw.bottom / 2;
	if (m_CenterPos.x + iHalfX > g_rtClient.right)
	{
		m_fDir[0] *= -1.0f;
		m_CenterPos.x = g_rtClient.right - iHalfX;
	}
	if (m_CenterPos.y + iHalfY > g_rtClient.bottom)
	{
		m_fDir[1] *= -1.0f;
		m_CenterPos.y = g_rtClient.bottom - iHalfY;
	}
	if (m_CenterPos.x - iHalfX < g_rtClient.left)
	{
		m_fDir[0] *= -1.0f;
		m_CenterPos.x = g_rtClient.left + iHalfX;
	}
	if (m_CenterPos.y - iHalfY < g_rtClient.top)
	{
		m_fDir[1] *= -1.0f;
		m_CenterPos.y = g_rtClient.top + iHalfY;
	}
	m_posDraw.x += m_fDir[0] * m_fSpeed * g_fSecPerFrame;
	m_posDraw.y += m_fDir[1] * m_fSpeed * g_fSecPerFrame;
	m_CenterPos.x = m_posDraw.x + iHalfX;
	m_CenterPos.y = m_posDraw.y + iHalfY;
	return true;
}


NPCObj::NPCObj()
{
	m_fSpeed = 200.0f;
}


NPCObj::~NPCObj()
{
}
