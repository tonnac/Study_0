#pragma once
#include "UI.h"

class Item : public UI
{
public:
	Item(const INT& = 0);
public:
	bool	Frame() override;
	void	OneUse();
	INT		getNum();
private:
	INT		m_iNum;
};