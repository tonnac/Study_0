#include "Stack.h"

template<class T>
T Stack<T>::g_Null;

template<class T>
Stack<T>::Stack() : m_iTop(-1){}

template<class T>
Stack<T>::~Stack(){}

template<class T>
T&	Stack<T>::Push(T iData)
{
	if (m_iTop == g_iMaxStack-1)
	{
		std::cout << "Stack Overflow" << std::endl;
		return g_Null;
	}
	m_iStackArray[++m_iTop] = iData;
	return iData;
}

template<class T>
T&	Stack<T>::Pop()
{
	if (m_iTop < 0)
	{
		std::cout << "Stack Underflow" << std::endl;
		return g_Null;
	}
	T& iRet = m_iStackArray[m_iTop--];
//	m_iStackArray[m_iTop--] = g_Null;  필요업다
	return iRet;
}

template<class T>
void Stack<T>::Show()
{
	for (int i = m_iTop; i >= 0; i--)
	{
		std::cout << m_iStackArray[i] << " " << std::endl;
	}
	std::cout << std::endl;
}