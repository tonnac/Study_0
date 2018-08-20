#include "TerrainObject.h"


bool TerrainObject::Init()
{
	return true;
}
bool TerrainObject::Frame()
{
	m_CenterPos.x = m_DrawPos.x + (m_rtDraw.right /2);
	m_CenterPos.y = m_DrawPos.y + (m_rtDraw.bottom / 2);

	m_rtCollision.left = static_cast<LONG>(m_DrawPos.x);
	m_rtCollision.top = static_cast<LONG>(m_DrawPos.y);
	m_rtCollision.right = static_cast<LONG>(m_DrawPos.x + m_rtDraw.right);
	m_rtCollision.bottom = static_cast<LONG>(m_DrawPos.y + m_rtDraw.bottom);
	return true;
}
bool TerrainObject::Render()
{
	//int prevpen = SetROP2(g_hOffScreenDC, R2_NOTXORPEN);

	//Rectangle(g_hOffScreenDC, m_rtCollision.left, m_rtCollision.top,
	//	m_rtCollision.right, m_rtCollision.bottom);

	//SetROP2(g_hOffScreenDC, prevpen);

	HBRUSH recbrush = CreateSolidBrush(RGB(0, 0, 255));

	RECT rt = { m_rtCollision.left,m_rtCollision.top,m_rtCollision.right,m_rtCollision.bottom };
	FillRect(g_hOffScreenDC, &rt, recbrush);

	return true;
}
bool TerrainObject::Release()
{
	return true;
}
bool TerrainObject::Collision(Object* pObject)
{
	RECT CollisionArea;
	RECT ObjRT = *(pObject->getCollisionRt());
	POINT Center;
	Center.x = (ObjRT.right + ObjRT.left) / 2;
	Center.y = (ObjRT.bottom + ObjRT.top) / 2;



	LONG xDiff = static_cast<LONG>(abs(Center.x - m_CenterPos.x));
	LONG yDiff = static_cast<LONG>(abs(Center.y - m_CenterPos.y));

	if (xDiff < (ObjRT.right - Center.x) + ((m_rtCollision.right - m_CenterPos.x)) &&
		yDiff < (ObjRT.bottom - Center.y) + ((m_rtCollision.bottom - m_CenterPos.y)))
	{
		CollisionArea.left = (ObjRT.left < m_rtCollision.left) ? m_rtCollision.left : ObjRT.left;
		CollisionArea.right = (ObjRT.right > m_rtCollision.right) ? m_rtCollision.right : ObjRT.right;
		CollisionArea.top = (ObjRT.top < m_rtCollision.top) ? m_rtCollision.top : ObjRT.top;
		CollisionArea.bottom = (ObjRT.bottom > m_rtCollision.bottom) ? m_rtCollision.bottom : ObjRT.bottom;
		return MoveObject(pObject, CollisionArea);
	}
	return false;
}
bool TerrainObject::MoveObject(Object* pObject, const RECT& CollisionArea)
{
	LONG lWidth = CollisionArea.right - CollisionArea.left;
	LONG lHeight = CollisionArea.bottom - CollisionArea.top;
	FloatPoint pObjCenterPos = *(pObject->getCenterPos());
	if (lWidth > lHeight)
	{
		if (CollisionArea.top == m_rtCollision.top)					//	위에서 충돌
		{
			Player * pl = dynamic_cast<Player*>(pObject);
			bool flag = pl->isFallState();
			if (flag == true)
			{
				pObject->setCenterPos_y(pObjCenterPos.y - lHeight + 7);
			}
			else
			{
				pObject->setCenterPos_y(pObjCenterPos.y - lHeight);
			}
			pObject->setLanding(true);
		}
		else if (CollisionArea.bottom == m_rtCollision.bottom)		// 아래에서 충돌
		{
			pObject->setCenterPos_y(pObjCenterPos.y + lHeight);
		}
	}
	else
	{
		if (CollisionArea.left == m_rtCollision.left)				// 왼쪽에서 충돌
		{
			pObject->setCenterPos_x(pObjCenterPos.x - (lWidth + 2));
			pObject->setLanding(false);
		}
		else if (CollisionArea.right == m_rtCollision.right)		// 오른쪽에서 충돌
		{
			pObject->setCenterPos_x(pObjCenterPos.x + lWidth + 2);
			pObject->setLanding(false);
		}
	}
	return true;
}

void TerrainObject::ReverseSet(const LONG& drawright)
{
	m_DrawPos.x -= drawright;
}