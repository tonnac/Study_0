#include "TEmployeee.h"



TEmployeee::TEmployeee(const char * _name, int _paytype) : m_iPayType(_paytype)
{
	m_cName = new char[strlen(_name) + 1];
	strcpy(m_cName, _name);
}


TEmployeee::~TEmployeee()
{
}
