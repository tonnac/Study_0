#pragma once
#include <iostream>



class Queue
{
private:
	static const int g_iMaxQueue = 5;
	int		m_iQueueArray[g_iMaxQueue];
	int		m_iFront;
	int		m_iRear;
public:
	int		Get();
	int		Put(const int& iData);
	void	Show() const;
	void	NextPosidx(int& pos);
public:
	Queue();
	virtual ~Queue();
};