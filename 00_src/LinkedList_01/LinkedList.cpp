#include "LinkedList.h"


LinkedList::LinkedList(const int& Value) : m_iNumCounter(1)
{
	Head = new Node(Value);
	Tail = Head;
}
LinkedList::~LinkedList()
{
	int i = 0;
	Node * Del = Head;
	Node * temp = Head;
	while(i++<m_iNumCounter)
	{
		temp = Del->m_pNext;
		delete Del;
		Del = temp;
	}
}

void LinkedList::AddLink(const int& Value)
{
	Tail->m_pNext = new Node(Value);
	Tail = Tail->m_pNext;
	m_iNumCounter++;
}
void LinkedList::AddLink(Node * data)
{
	Tail->m_pNext = data;
	Tail = Tail->m_pNext;
	m_iNumCounter++;
}
void LinkedList::DelLink(const int& Value)
{
	if (Head->m_iValue == Value)
	{
		DelLink(Head);
		return;
	}
	Node * pNode = Head;
	while (pNode->m_pNext != NULL)
	{
		if (pNode->m_pNext->m_iValue == Value)
		{
			break;
		}
		pNode = pNode->m_pNext;
	}
	Node * DelNode = pNode->m_pNext;
	pNode->m_pNext = DelNode->m_pNext;
//	DelLink(DelNode);
	if (Tail == DelNode)
	{
		Tail = pNode;
	}
	delete DelNode;
	m_iNumCounter--;
}
void LinkedList::DelLink(Node * data)
{
	if (Head == data)
	{
		Head = Head->m_pNext;
		Tail->m_pNext = Head;
		m_iNumCounter--;
		delete data;
		return;
	}
	Node * pNode = Head;	
	while (pNode->m_pNext != NULL)
	{
		if (pNode->m_pNext == data)
		{
			break;
		}
		pNode = pNode->m_pNext;
	}
	pNode->m_pNext = data->m_pNext;
	if (data == Tail)
	{
		Tail = pNode;
	}
	delete data;
	m_iNumCounter--;
}
void LinkedList::PrintLink() const
{
	Node * temp = Head;
	for (int i = 0; i < m_iNumCounter;
		i++, temp = temp->m_pNext)
	{
		cout << temp->m_iValue << endl;
	}
}