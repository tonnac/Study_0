#pragma once
#include "SvrUtil.h"
class SvrObject
{
public:
	CRITICAL_SECTION m_cs;
public:
	SvrObject();
	virtual ~SvrObject();
};