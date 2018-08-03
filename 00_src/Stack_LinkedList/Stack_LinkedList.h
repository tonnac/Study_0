#pragma once

template<class K>
class Stack
{
public:
	Stack();
	Stack<K> * m_pNext;
	K data;
private:
};