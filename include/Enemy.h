#pragma once
#include "CharacterObject.h"

class Enemy : public CharacterObject
{
public:
	Enemy();
	~Enemy();
public:
	bool		Frame() override;
private:
};