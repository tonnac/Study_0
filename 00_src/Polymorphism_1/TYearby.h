#pragma once
#include "TEmployee.h"
class TYearby : public TEmployee
{
private:
	const int m_iGrade;
	const int m_iPay;
public:
	void Salaryinput();
	TYearby(const char * _name, const int& _Pos, const int& _grade)
		: TEmployee(_name, _Pos), m_iGrade(_grade),m_iPay(20000000)
	{
		Salaryinput();
	}
	~TYearby();
};

