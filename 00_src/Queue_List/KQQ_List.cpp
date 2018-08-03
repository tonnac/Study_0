#include "KQQ_List.h"
#include <iostream>

using namespace std;

template <class K>
void KQQ_List<K>::put(const K & data)
{
	KQ_List<K> * NewNode = new KQ_List<K>;
	NewNode->data = data;
	if (m_pHead == nullptr)
	{
		m_pHead = NewNode;
		m_pTail = NewNode;
		m_pHead->m_pNext = m_pTail;
	}
	m_pTail->m_pNext = NewNode;
	m_pTail = m_pTail->m_pNext;
}

template <class K>
bool KQQ_List<K>::peek(K & data)
{
	if (empty())
	{
		cout << "Memory ERROR" << endl;
		return false;
	}
	data = m_pHead->data;
	return true;
}

template <class K>
void KQQ_List<K>::pop()
{
	if (empty())
	{
		cout << "Memory ERROR" << endl;
		return;
	}
	KQ_List<K> * DelNode = m_pHead;
	m_pHead = m_pHead->m_pNext;
	delete DelNode;
}

template <class K>
bool KQQ_List<K>::empty() const
{
	if (m_pHead == nullptr)
		return true;
	return false;
}

template <class K>
void KQQ_List<K>::show() const
{
	KQ_List<K> * temp = m_pHead;
	while (temp != nullptr)
	{
		cout << temp->data << " ";
		temp = temp->m_pNext;
	}
}


template <class K>
KQQ_List<K>::KQQ_List() : m_pHead(nullptr), m_pTail(nullptr){}

template <class K>
KQQ_List<K>::~KQQ_List()
{
	KQ_List<K> * temp = m_pHead;
	while (m_pHead != nullptr)
	{
		m_pHead = m_pHead->m_pNext;
		delete temp;
		temp = m_pHead;
	}
}