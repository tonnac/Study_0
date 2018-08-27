#pragma once
#include "TEnemy.h"
class TAttackAction : public TEnemyState
{
public:
	bool Process(TObject* pTarget);
public:
	TAttackAction(TEnemy* pParent);
	virtual ~TAttackAction();
};

