#pragma once
#include "TObject.h"
class TEnemy;

class TEnemyState
{
protected:
	TEnemy*  m_pOwner;
public:
	virtual bool Process(TObject* pTarget) = 0;
public:
	TEnemyState(TEnemy*);
	virtual ~TEnemyState();
};

