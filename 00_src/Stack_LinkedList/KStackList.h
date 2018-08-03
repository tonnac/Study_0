#pragma once
#include "Stack_LinkedList.h"

template <class K>
class KStackList
{
public:
	void push(K data);
	K pop();
	bool empty();
	void show() const;
	K peek();
	KStackList();
	~KStackList();
private:
	Stack<K> * m_pHead;
	Stack<K> * m_pTail;
};

