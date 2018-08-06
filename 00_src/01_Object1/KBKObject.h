#pragma once
#include "KObject.h"
class KBKObject : public KObject
{
public:
	bool		Frame() { return true; }
public:
				KBKObject();
	virtual		~KBKObject();
};

