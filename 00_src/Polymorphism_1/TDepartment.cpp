#include "TDepartment.h"



void TDepartment::AddEmployee(TEmployee * add)
{
	emp[m_iIndex++] = add;
}

void TDepartment::ShowSalary()
{
	for (int i = 0; i < m_iIndex; i++)
	{
		std::cout << "�̸�: " << emp[i]->GetName() << std::endl;
		std::cout << "�޿�: " << emp[i]->GetSalary() << std::endl << std::endl;
	}
}

TDepartment::TDepartment() : m_iIndex(0)
{
}


TDepartment::~TDepartment()
{
	for (int i = 0; i < m_iIndex; i++)
	{
		delete emp[i];
	}
}
