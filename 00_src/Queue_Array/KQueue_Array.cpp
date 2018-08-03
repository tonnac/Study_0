#include "KQueue_Array.h"
#include <iostream>

using namespace std;

template <class K>
KQueue_Array<K>::KQueue_Array() : m_iFront(0), m_iRear(0){}

template <class K>
bool KQueue_Array<K>::put(const K & data)
{
	if (m_iFront == (m_iRear + 1) % MAX_LEN)
	{
		cout << "Overflow" << endl;
		return false;
	}
	m_iRear = ++m_iRear % MAX_LEN;
	karr[m_iRear] = data;
	return true;
}
template <class K>
bool KQueue_Array<K>::peek(K & data)
{
	if (empty())
	{
		cout << "MEMORY ERROR" << endl;
		return false;
	}
	data = karr[m_iFront+1];
	return true;
}
template <class K>
void KQueue_Array<K>::pop()
{
	if (empty())
	{
		cout << "MEMORY ERROR" << endl;
		return;
	}
	m_iFront = ++m_iFront % MAX_LEN;
	karr[m_iFront] = 0;
}
template <class K>
bool KQueue_Array<K>::empty() const
{
	if (m_iFront == m_iRear)
		return true;
	return false;
}
template <class K>
void KQueue_Array<K>::show() const
{
	for (int i = m_iFront + 1; i <= m_iRear; i++)
	{
		cout << karr[i] << " ";
	}
	cout << endl << endl;
}