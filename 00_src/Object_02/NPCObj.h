#pragma once
#include "KObject.h"
class NPCObj : public KObject
{
public:
	bool			Frame()override;
public:
	NPCObj();
	virtual ~NPCObj();
};

