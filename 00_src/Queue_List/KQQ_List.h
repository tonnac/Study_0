#pragma once
#include "KQ_List.h"

template <class K>
class KQQ_List
{
public:
	KQQ_List();
	~KQQ_List();
	void put(const K & data);
	bool peek(K & data);
	void pop();
	bool empty() const;
	void show() const;
private:
	KQ_List<K> * m_pHead;
	KQ_List<K> * m_pTail;
};

