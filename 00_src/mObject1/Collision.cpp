#include "Collision.h"

// RectÀÇ Á¾·ù
// x,y -> w
//  |
//  h
// x1,y1   x2,y1
//
// x1,y2   x2,y2


bool Collision::RectInRect(RECT rtDesk, RECT rtSrc)
{
	POINT cCenterDesk, cCenterSrc;
	cCenterDesk.x = (rtDesk.left + (rtDesk.left + rtDesk.right)) / 2;
	cCenterDesk.y = (rtDesk.top + (rtDesk.top + rtDesk.bottom)) / 2;
	cCenterSrc.x = (rtSrc.left + (rtSrc.left + rtSrc.right)) / 2;
	cCenterSrc.y = (rtSrc.top + (rtSrc.top + rtSrc.bottom)) / 2;
	if(abs(cCenterDesk.x - cCenterSrc.x) < abs(rtDesk.right / 2) + abs(rtSrc.right / 2) &&
		abs(cCenterDesk.y - cCenterSrc.y) < abs((rtDesk.bottom / 2) + abs(rtSrc.bottom / 2)))
	{
		return true;
	}
	return false;
}
bool Collision::RectInPt(RECT rt, POINT pt)
{
	if (rt.left <= pt.x && rt.right >= pt.x)
	{
		if (rt.top <= pt.y && rt.bottom >= pt.y)
		{
			return true;
		}
	}
	return false;
}
bool Collision::SphereInSphere(RECT rt, RECT rtSrc)
{
	return false;
}
bool Collision::SphereInPt(RECT rt, RECT rtSrc)
{
	return false;
}

Collision::Collision()
{
}


Collision::~Collision()
{
}
