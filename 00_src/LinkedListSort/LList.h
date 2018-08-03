#pragma once
class LList
{
public:
	int m_iValue;
	LList * m_pPrev;
	LList * m_pNext;
public:
	LList();
	LList(const int& number);
};

