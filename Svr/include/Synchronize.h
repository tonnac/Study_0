#pragma once
#include "SvrObject.h"
class Synchronize
{
public:
	SvrObject* m_pSerObj;
public:
	Synchronize(SvrObject * pSerObj);
	virtual ~Synchronize();
};