#pragma once
#include "TTimeby.h"
#include "TYearby.h"
#include "TMonthby.h"

class TDepartment
{
private:
	TEmployee * emp[10];
	int m_iIndex;
public:
	void AddEmployee(TEmployee * add);
	void ShowSalary();
	TDepartment();
	~TDepartment();
};

