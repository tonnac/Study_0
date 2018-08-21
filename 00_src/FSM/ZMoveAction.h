#pragma once
#include "ZEnemy.h"

class ZMoveAction : public ZEnemyState
{
public:
	bool Process(KObject * pTarget) override;
public:
	ZMoveAction(ZEnemy * pOwner);
	virtual ~ZMoveAction();
};

