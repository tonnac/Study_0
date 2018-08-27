#pragma once
#include "TEnemy.h"
class TMoveAction : public TEnemyState
{
public:
	bool Process(TObject* pTarget);
public:
	TMoveAction(TEnemy* pParent);
	virtual ~TMoveAction();
};

