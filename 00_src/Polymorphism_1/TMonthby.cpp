#include "TMonthby.h"


void TMonthby::Salaryinput()
{
	int salary;
	int pos = TEmployee::GetPos();
	int posrate = pos * 200000;
	int yearrate = m_iYear * 50000;
	salary = m_iPay + posrate + yearrate;
	TEmployee::inputSalary(salary);
}



TMonthby::~TMonthby()
{
}
