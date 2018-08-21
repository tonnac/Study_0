#pragma once
#include "Object.h"

class State;

using StateMap = std::map<std::string, State*>;

class CharacterObject : public Object
{
public:
	CharacterObject();
public:
	virtual bool 	Init			() override;
	virtual bool 	Frame			() override;
	virtual bool 	Render			() override;
	virtual bool 	Release			() override;
public:
	void			setState		(T_STR);
	void			setDir			(const INT&);
	void			setLadder		(const bool&);
	void			setJumpSpeed	(const FLOAT&, const FLOAT& = 0.0f);
	void			setJumpNum		(const INT&);
	void			setDownable		(const bool&);
public:
	std::string		getCurrentState	();
	bool			getDownable		();
	INT				getDir			();
	FLOAT&			getJumpSpeed	(const INT& = 0);
	bool			getLadder		();
	INT				getJumpNum		();
	bool			isFallState		();
public:
	void			addState		(std::string, State*);
protected:
	INT				m_iJumpNumber;
	bool			m_bLadder;
	bool			m_bDownable;
	FLOAT			m_fJumpSpeed;
	FLOAT			m_fJumpSpeed2;
	INT				m_iCurrentDir;
	StateMap		m_pStateList;
	State *			m_pCurrentState;
};