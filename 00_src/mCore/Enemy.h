#pragma once
#include "CharacterObject.h"
#include "EnemyBasicState.h"
#include "FinateStateMachine.h"

class Enemy : public CharacterObject
{
public:
	Enemy();
	~Enemy();
public:
	bool		Frame() override;
private:
};