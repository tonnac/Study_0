#include "Scroll.h"
#include "Player.h"

Scroll::Scroll(Object * pPlayer, Object * pBkObj) : m_pPlayer(pPlayer),
		m_PlayerCollisionRt(pPlayer->getCollisionRt()), m_pBkObj(pBkObj),
		m_BkRtDraw(pBkObj->getrtDraw())
{}

bool Scroll::Init()
{
	m_rtCollision.left = g_rtClient.left + 200;
	m_rtCollision.top = g_rtClient.top;
	m_rtCollision.right = (g_rtClient.left + 520 + g_rtClient.right) / 2;
	m_rtCollision.bottom = g_rtClient.bottom;

	m_CenterPos.x = static_cast<FLOAT>((m_rtCollision.left + m_rtCollision.right) / 2);
	m_CenterPos.y = static_cast<FLOAT>((m_rtCollision.top + m_rtCollision.bottom) / 2);

	m_nInitValue.at(0) = m_BkRtDraw->left;
	m_nInitValue.at(1) = m_BkRtDraw->left + m_BkRtDraw->right;
	return true;
}
bool Scroll::Frame()
{
	Collision(*m_PlayerCollisionRt);
	return true;
}
bool Scroll::Render()
{
	int prevpen = SetROP2(g_hOffScreenDC, R2_NOTXORPEN);
	Rectangle(g_hOffScreenDC, m_rtCollision.left, m_rtCollision.top,
		m_rtCollision.right, m_rtCollision.bottom);

	SetROP2(g_hOffScreenDC, prevpen);
	return true;
}
bool Scroll::Release()
{
	return true;
}
bool Scroll::Collision(const RECT& rt)
{
	LONG x1;			//충돌영역 계산
	
	POINT A_Center;
	A_Center.x = (rt.right + rt.left) / 2;
	A_Center.y = (rt.bottom + rt.top) / 2;

	LONG size = rt.right - rt.left;

	LONG xDiff = static_cast<LONG>(abs(A_Center.x - m_CenterPos.x));
	LONG yDiff = static_cast<LONG>(abs(A_Center.y - m_CenterPos.y));

	if (rt.right >= m_rtCollision.right)
	{
		x1 = rt.right - m_rtCollision.right;
		if ((m_nInitValue[1] - m_BkRtDraw->left)
			<= g_rtClient.right)  // 화면 끝 도달
		{
			return true;
		}
		return MoveCamera(x1);
	}

	if (rt.left <= m_rtCollision.left)
	{
		x1 = rt.left - m_rtCollision.left;
		if (m_BkRtDraw->left - m_nInitValue[0] <= g_rtClient.left)  // 화면 끝 도달
		{
			return true;
		}
		Player * pl = dynamic_cast<Player*>(m_pPlayer);
		if (pl->getDir() == -1)
		{
			return MoveCamera(x1);
		}
	}
	return true;
}


bool Scroll::MoveCamera(const LONG& size)
{
	FLOAT x = (*m_pPlayer->getCenterPos()).x;
	m_pPlayer->setCenterPos_x(x - size);
	m_pBkObj->MoveScrollBk(size);
	return true;
}