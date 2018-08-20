#pragma once
#include "Object.h"

class State;

using StateMap = std::map<std::string, State*>;

class Player : public Object
{
public:
	Player();
public:
	bool			Init			() override;
	bool			Frame			() override;
	bool			Render			() override;
	bool			Release			() override;
public:
	void			setState		(T_STR);
	void			setJumpNum		(const INT&);
	void			setDir			(const INT&);
public:
	INT				getDir			();
	INT				getJumpNum		();
	bool			isFallState		();
public:
	void			addState		(std::string, State*);
private:
	INT				m_iCurrentDir;
	INT				m_iJumpNumber;
	StateMap		m_pStateList;
	State *			m_pCurrentState;
};