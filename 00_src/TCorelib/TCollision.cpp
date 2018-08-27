#include "TCollision.h"
// x,y -> w
//  |  c
//  h
// x1,y1   x2,y1
//
// x1,y2   x2,y2  
bool	TCollision::RectInRect(RECT rtDesk, RECT rtSrc)
{
	POINT cDesk,cSrc;
	cDesk.x = (rtDesk.left + rtDesk.right) / 2;
	cDesk.y = (rtDesk.top + rtDesk.bottom) / 2;
	cSrc.x = (rtSrc.left + rtSrc.right) / 2;
	cSrc.y = (rtSrc.top + rtSrc.bottom) / 2;

	POINT radius;
	radius.x = abs(cDesk.x - cSrc.x);
	radius.y = abs(cDesk.y - cSrc.y);

	POINT deskRadius, srcRadius;
	deskRadius.x = (rtDesk.right - rtDesk.left) / 2;
	deskRadius.y = (rtDesk.bottom - rtDesk.top) / 2;
	srcRadius.x = (rtSrc.right - rtSrc.left) / 2;
	srcRadius.y = (rtSrc.bottom - rtSrc.top) / 2;

	if (radius.x <= (deskRadius.x+ srcRadius.x)
		&&
		radius.y <= (deskRadius.y + srcRadius.y))
	{
		return true;
	}

	return false;
}
bool	TCollision::RectInPt(RECT rt, POINT pt) 
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
bool	TCollision::RectInPt(RECT rt, tPoint pt)
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
bool	TCollision::SphereInSphere(
	RECT rtDesk,
	RECT rtSrc) 
{
	TSphere sphereDesk, sphereSrc;
	sphereDesk.pCenter.x = (rtDesk.left + rtDesk.right) / 2;
	sphereDesk.pCenter.y = (rtDesk.top + rtDesk.bottom) / 2;
	LONG dwX = (rtDesk.right - rtDesk.left) / 2;
	LONG dwY = (rtDesk.bottom - rtDesk.top) / 2;
	sphereDesk.fRadius = (dwX < dwY) ? dwY : dwX;

	sphereSrc.pCenter.x = (rtSrc.left + rtSrc.right) / 2;
	sphereSrc.pCenter.y = (rtSrc.top + rtSrc.bottom) / 2;
	dwX = (rtSrc.right - rtSrc.left) / 2;
	dwY = (rtSrc.bottom - rtSrc.top) / 2;
	sphereSrc.fRadius = (dwX < dwY) ? dwY : dwX;

	float fDistance =
		sqrt((sphereDesk.pCenter.x - sphereSrc.pCenter.x)*
		(sphereDesk.pCenter.x - sphereSrc.pCenter.x) +
			(sphereDesk.pCenter.y - sphereSrc.pCenter.y)*
			(sphereDesk.pCenter.y - sphereSrc.pCenter.y));

	if (fDistance < (sphereDesk.fRadius+
		sphereSrc.fRadius))
	{
		return true;
	}

	return false;
}
bool	TCollision::SphereInPt(RECT rtDesk, POINT pt) 
{
	TSphere sphereDesk;
	sphereDesk.pCenter.x = (rtDesk.left + rtDesk.right) / 2;
	sphereDesk.pCenter.y = (rtDesk.top + rtDesk.bottom) / 2;
	LONG dwX = (rtDesk.right - rtDesk.left) / 2;
	LONG dwY = (rtDesk.bottom - rtDesk.top) / 2;
	sphereDesk.fRadius = (dwX < dwY) ? dwY : dwX;

	float fDistance =
		sqrt((sphereDesk.pCenter.x - pt.x)*
			(sphereDesk.pCenter.x - pt.x) +
			(sphereDesk.pCenter.y - pt.y)*
			(sphereDesk.pCenter.y - pt.y));

	if (fDistance < sphereDesk.fRadius)
	{
		return true;
	}
	return false;
}


TCollision::TCollision()
{
}


TCollision::~TCollision()
{
}
