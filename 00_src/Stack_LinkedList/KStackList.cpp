#include "KStackList.h"
#include <iostream>

template <class K>
KStackList<K>::KStackList() : m_pHead(nullptr), m_pTail(nullptr)
{}

template <class K>
KStackList<K>::~KStackList()
{
	Stack<K> * temp = m_pHead;
	while (m_pHead != nullptr)
	{
		m_pHead = m_pHead->m_pNext;
		delete temp;
		temp = m_pHead;
	}
}
template <class K>
void KStackList<K>::push(K data)
{
	if (m_pHead == nullptr)
	{
		Stack<K> * temp = new Stack<K>;
		temp->data = data;
		m_pHead = temp;
		m_pTail = temp;
		return;
	}
	Stack<K> * temp = new Stack<K>;
	temp->data = data;
	temp->m_pNext = m_pHead;
	m_pHead = temp;
}
template <class K>
K KStackList<K>::pop()
{
	if (m_pHead == m_pTail)
	{
		K rn = m_pHead->data;
		delete m_pHead;
		m_pHead = nullptr;
		return rn;
	}
	Stack<K> * temp = m_pHead;
	K rn = temp->data;
	m_pHead = m_pHead->m_pNext;
	delete temp;
	return rn;
}
template <class K>
bool KStackList<K>::empty()
{
	if (m_pHead == nullptr)
		return true;
	return false;
}
template <class K>
void KStackList<K>::show() const
{
	Stack<K> * temp = m_pHead;
	while (temp != nullptr)
	{
		std::cout << temp->data << " ";
		temp = temp->m_pNext;
	}
}
template <class K>
K KStackList<K>::peek()
{
	return m_pHead->data;
}