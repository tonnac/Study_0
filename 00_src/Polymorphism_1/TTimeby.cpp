#include "TTimeby.h"


void TTimeby::Salaryinput()
{
	int salary;
	int pos = TEmployee::GetPos();
	salary = (m_iWorkingTime * m_iPay);
	for (int i = 0; i < pos; i++)
	{
		salary *= 2;
	}
	TEmployee::inputSalary(salary);
}



TTimeby::~TTimeby()
{
}
