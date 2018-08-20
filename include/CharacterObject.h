#pragma once
#include "Object.h"

class State;

using StateMap = std::map<std::string, State*>;

class CharacterObject : public Object
{
public:
	CharacterObject();
public:
	virtual bool 	Init		() override;
	virtual bool 	Frame		() override;
	virtual bool 	Render		() override;
	virtual bool 	Release		() override;
public:
	void			setState	(T_STR);
	void			setDir		(const INT&);
public:
	INT				getDir		();
	bool			isFallState	();
public:
	void			addState	(std::string, State*);
protected:
	INT				m_iCurrentDir;
	StateMap		m_pStateList;
	State *			m_pCurrentState;
};