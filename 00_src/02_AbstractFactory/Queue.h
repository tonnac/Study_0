#pragma once
#include "DataStructure.h"

template <typename K>
class Queue : public DataStructure<K>
{
public:
	Queue()
	{
		DataStructure<K>::m_iFront = 0;
		DataStructure<K>::m_iRear = 0;
	}
	push<K> * createpush() { return new queuepush<K>; }
	pop<K> * createpop() { return new queuepop<K>; }
	empty<K> * createempty() { return new queueempty<K>; }
	print<K> * createprint() { return new queueprint<K>; }
};
