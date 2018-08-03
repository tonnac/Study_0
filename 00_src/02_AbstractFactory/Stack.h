#pragma once
#include "DataStructure.h"

template <typename K>
class Stack : public DataStructure<K>
{
public:
	Stack()
	{
		DataStructure<K>::m_iIndex = -1;
	}
	push<K> * createpush() { return new stackpush<K>; }
	pop<K> * createpop() {return new stackpop<K>;}
	empty<K> * createempty() { return new stackempty<K>; }
	print<K> * createprint() { return new stackprint<K>; }
};
