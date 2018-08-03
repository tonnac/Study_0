#include "CmpClass.h"


bool CmpClass::operator > (const CmpClass& src)
{
	if (m_iValue >= src.m_iValue) { return true; }

	return false;
}
bool CmpClass::operator < (const CmpClass& src)
{
	if (m_iValue < src.m_iValue) { return true; }

	return false;
}

CmpClass::CmpClass(const int& data) : m_iValue(data)
{}


CmpClass::~CmpClass()
{
}
