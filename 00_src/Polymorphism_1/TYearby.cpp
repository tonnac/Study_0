#include "TYearby.h"

void TYearby::Salaryinput()
{
	int salary;
	int pos = TEmployee::GetPos();
	salary = (m_iPay + (pos*m_iPay / 2) + (m_iPay / 4)*m_iGrade) / 12;
	TEmployee::inputSalary(salary);
}

TYearby::~TYearby()
{
}
