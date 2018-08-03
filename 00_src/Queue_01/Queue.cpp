#include "Queue.h"
#include <iostream>

int Queue::Get()
{
	if (m_iFront == m_iRear)
	{
		std::cout << "Queue Underflow" << std::endl;
	}
	int iValue = m_iQueueArray[m_iFront];
	m_iQueueArray[m_iFront] = -1;
	m_iRear = ++m_iRear % g_iMaxQueue;
	return iValue;
}
int	Queue::Put(const int& iData)
{
	if ((m_iRear+1) % g_iMaxQueue ==
		m_iFront)
	{
		std::cout << "Queue Overflow" << std::endl;
		return -1;
	}
	m_iQueueArray[m_iRear] = iData;
	m_iRear = ++m_iRear % g_iMaxQueue;
}
void Queue::Show() const
{

}
void Queue::NextPosidx(int& pos)
{
	if (pos + 1 == g_iMaxQueue)
	{
		pos = 0;
	}
	pos = pos + 1;
}

Queue::Queue() : m_iFront(0), m_iRear(0) {}


Queue::~Queue()
{

}
