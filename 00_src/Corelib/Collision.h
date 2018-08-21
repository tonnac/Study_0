#pragma once
#include "WindowClass.h"
#include <cmath>

struct Sphere
{
	POINT pCenter;
	float fRadius;
};

class Collision
{
public:
	static bool			RectInRect(RECT rtDesk, RECT rtSrc);
	static bool			RectInPt(RECT rt, POINT pt);
	static bool			RectInPt(RECT rt, KPoint pt);
	static bool			SphereInSphere(RECT rtDesk, RECT rtSrc);
	static bool			SphereInPt(RECT rtDesk, POINT pt);
public:
	Collision();
	virtual ~Collision();
};