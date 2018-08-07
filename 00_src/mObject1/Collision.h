#pragma once
#include "WindowClass.h"

class Collision
{
public:
	static bool			RectInRect(RECT rtDesk, RECT rtSrc);
	static bool			RectInPt(RECT rt, POINT pt);
	static bool			SphereInSphere(RECT rtDesk, RECT rtSrc);
	static bool			SphereInPt(RECT rtDesk, RECT rtSrc);
public:
	Collision();
	virtual ~Collision();
};