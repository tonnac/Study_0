#pragma once
#include "UI.h"

class Inventory : public UI
{
public:
	Inventory();
public:
	bool		Frame();
private:
	INT			m_iIndex;
};

class InGameMenu : public UI
{
public:
	InGameMenu();
public:
	bool		Frame() override;
private:
	INT			m_iIndex;
	Inventory	m_iInventory;
};