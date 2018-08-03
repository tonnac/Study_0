#include "TEmployee.h"



TEmployee::TEmployee(const char * _name, const int& _Pos)
	: m_iPos(_Pos), m_iSalary(0)
{
	m_cName = new char[strlen(_name) + 1];
	strcpy(m_cName, _name);
}

int TEmployee::GetSalary() const{return m_iSalary;}
char* TEmployee::GetName() const{return m_cName;}
int TEmployee::GetPos() const{return m_iPos;}
void TEmployee::inputSalary(const int& money){m_iSalary = money;}


TEmployee::~TEmployee()
{
	delete[]m_cName;
}
