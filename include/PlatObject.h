#pragma once
#include "TerrainObject.h"

class PlatObject : public TerrainObject
{
public:
	bool				Init() override;
	virtual bool		Frame() override;
	bool				Render() override;
	bool				Release() override;
};