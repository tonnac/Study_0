#pragma once
#include "TEnemy.h"

class TStandAction : public TEnemyState
{
public:
	bool Process(TObject* pTarget);
public:
	TStandAction(TEnemy* pParent);
	virtual ~TStandAction();
};

