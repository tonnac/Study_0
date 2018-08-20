#pragma once
#include "TerrainObject.h"

class DownableObject : public TerrainObject
{
public:
	virtual bool		Collision(Object*) override;
	virtual	bool		MoveObject(Object*, const RECT&) override;
};