#pragma once
#include "CharacterObject.h"

class TerrainObject;

class BKObject : public Object
{
public:
	BKObject();
public:
//	bool		Init			() override;
	bool		Frame			() override;
	bool		Render			() override;
	bool		Release			() override;
	bool		MoveScrollBk	(const LONG&) override;
	void		AddTerrain		(TerrainObject *);
	bool		Collision		(Object* ) override;
	void		ReverseSet		();
private:
	std::vector<TerrainObject*> m_pObjList;
};