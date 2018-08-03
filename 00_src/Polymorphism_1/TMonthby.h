#pragma once
#include "TEmployee.h"
class TMonthby : public TEmployee
{
private:
	const int m_iYear;
	const int m_iPay;
public:
	void Salaryinput();
	TMonthby(const char * _name, const int& _Pos, const int& _year)
		:TEmployee(_name, _Pos), m_iYear(_year), m_iPay(2000000)
	{
		Salaryinput();
	}
	~TMonthby();
};

