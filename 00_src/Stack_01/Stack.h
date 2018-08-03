#pragma once
#include <iostream>

const int g_iMaxStack = 10;

template<class T>
class Stack
{
public:
	T	m_iStackArray[g_iMaxStack];
	int		m_iTop;
public:
	T&		Push(T iData);
	T&		Pop();
	void	Show(); //연산자 재정의해야댐
	static  T g_Null;
public:
	Stack();
	virtual ~Stack();
};

