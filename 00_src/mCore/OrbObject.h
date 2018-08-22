#pragma once
#include "TerrainObject.h"

class OrbObject : public TerrainObject
{
public:
	bool		Collision(Object*) override;
private:
};