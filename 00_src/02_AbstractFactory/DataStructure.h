#pragma once
#include "BasicFunction.h"

template <typename K>
class DataStructure
{
public:
	virtual push<K> * createpush() = 0;
	virtual pop<K> * createpop() = 0;
	virtual empty<K> * createempty() = 0;
	virtual print<K> * createprint() = 0;
public:
	static const int LEN = 10;
	int m_iIndex;
	K arr[LEN];
public:
	int m_iFront;
	int m_iRear;
};

