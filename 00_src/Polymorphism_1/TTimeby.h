#pragma once
#include "TEmployee.h"
class TTimeby : public TEmployee
{
private:
	const int m_iWorkingTime;
	const int m_iPay;
public:
	void Salaryinput();
	TTimeby::TTimeby(const char * _name, const int& _Pos, const int& _workingtime)
		:TEmployee(_name, _Pos), m_iWorkingTime(_workingtime),m_iPay(10000)
	{
		Salaryinput();
	}
	~TTimeby();
};

