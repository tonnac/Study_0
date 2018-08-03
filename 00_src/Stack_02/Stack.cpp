#include "Stack.h"
#include <iostream>


template<class K>
void Stack<K>::push(K data)
{
	if (m_iTop >= MAX_LEN - 1)
	{
		std::cout << "Stack overflow" << std::endl;
		return;
	}

	stcarr[++m_iTop] = data;
}

template<class K>
bool Stack<K>::empty()
{
	if (m_iTop < 0)
		return true;
	return false;
}

template<class K>
void Stack<K>::show() const
{
	for (int i = m_iTop; i >= 0; i--)
	{
		std::cout << stcarr[i] << " ";
	}
}
template<class K>
K Stack<K>::peek()
{
	return stcarr[m_iTop];
}

template<class K>
K Stack<K>::pop()
{
	if (empty())
	{
		std::cout << "Stack Underflow" << std::endl;
	}
	K data = stcarr[m_iTop];
	stcarr[m_iTop--] = 0;
	return data;
}

template<class K>
Stack<K>::Stack() : m_iTop(-1)
{}
template<class K>
Stack<K>::~Stack()
{}