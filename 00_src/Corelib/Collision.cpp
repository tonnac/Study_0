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

	POINT radius;
	radius.x = abs(cCenterDesk.x - cCenterSrc.x);
	radius.y = abs(cCenterDesk.y - cCenterSrc.y);

	POINT deskRadius, srcRadius;
	deskRadius.x = (rtDesk.right - rtDesk.left) * 0.5f;
	deskRadius.y = (rtDesk.bottom- rtDesk.top) * 0.5f;
	srcRadius.x = (rtSrc.right - rtSrc.left) * 0.5f;
	srcRadius.y = (rtSrc.bottom - rtSrc.top) * 0.5f;

	if(radius.x <= (deskRadius.x + srcRadius.x)
		&&
		radius.y <= (srcRadius.y + srcRadius.y))
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
bool Collision::SphereInSphere(RECT rtDesk, RECT rtSrc)
{
	Sphere sphereDesk, sphereSrc;
	sphereDesk.pCenter.x = (rtDesk.left + (rtDesk.left + rtDesk.right)) / 2;
	sphereDesk.pCenter.y = (rtDesk.top + (rtDesk.top + rtDesk.bottom)) / 2;

	sphereSrc.pCenter.x = (rtSrc.left + (rtSrc.left + rtSrc.right)) / 2;
	sphereSrc.pCenter.y = (rtSrc.top + (rtSrc.top + rtSrc.bottom)) / 2;

	LONG dwX = (rtDesk.right - rtDesk.left) / 2;
	LONG dwY = (rtDesk.bottom - rtDesk.top) / 2;

	sphereDesk.fRadius = (dwX < dwY) ? dwY : dwX;

	dwX = (rtSrc.right - rtSrc.left) / 2;
	dwY = (rtSrc.bottom - rtSrc.top) / 2;
	sphereSrc.fRadius = (dwX < dwY) ? dwY : dwX;

	float fDistance = sqrt((sphereDesk.pCenter.x - sphereSrc.pCenter.x) *
		(sphereDesk.pCenter.x - sphereSrc.pCenter.x) + (sphereDesk.pCenter.y - sphereSrc.pCenter.y)*
		(sphereDesk.pCenter.y - sphereSrc.pCenter.y));

	if (fDistance < (sphereDesk.fRadius + sphereDesk.fRadius))
	{
		return true;
	}

	return false;
}
bool Collision::SphereInPt(RECT rtDesk, POINT pt)
{
	Sphere sphereDesk;
	sphereDesk.pCenter.x = (rtDesk.left + (rtDesk.left + rtDesk.right)) / 2;
	sphereDesk.pCenter.y = (rtDesk.top + (rtDesk.top + rtDesk.bottom)) / 2;

	LONG dwX = (rtDesk.right - rtDesk.left) / 2;
	LONG dwY = (rtDesk.bottom - rtDesk.top) / 2;

	sphereDesk.fRadius = (dwX < dwY) ? dwY : dwX;

	float fDistance = sqrt((sphereDesk.pCenter.x - pt.x) *
		(sphereDesk.pCenter.x - pt.x) + (sphereDesk.pCenter.y - pt.y)*
		(sphereDesk.pCenter.y - pt.y));

	if (fDistance < sphereDesk.fRadius)
	{
		return true;
	}
	return false;
}

Collision::Collision()
{
}


Collision::~Collision()
{
}
