#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

class TToken1
{
private:
	static int m_iCounter;
	char * m_pCh;
	TToken1 * m_pNext;
	friend ostream& operator <<(ostream & os, const TToken1* data);
public:
	void addTToken(TToken1 * data);
	bool TTokenCheck(const char * pChar);
public:
	TToken1& operator+= (TToken1 * data);
public:
	TToken1() : m_pCh(NULL), m_pNext(NULL)
	{}
	TToken1(const char * data);
	~TToken1();
};