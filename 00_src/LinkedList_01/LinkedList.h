#pragma once
#include <iostream>
using namespace std;

class Node
{
public:
	int m_iValue;
	Node * m_pNext;
	friend class LinkedList;
	friend class CircularLinkedList;
public:
	Node(int Value = 0) : m_iValue(Value)
	{
		m_pNext = NULL;
	}
};
class LinkedList
{
public:
	int m_iNumCounter;
	Node * Head;
	Node * Tail;
public:
	LinkedList(const int& Value = 0);
	~LinkedList();
	virtual void AddLink(const int& Value);
	virtual void AddLink(Node * data);
	virtual void DelLink(const int& Value);
	void DelLink(Node * data);
	Node* GetTail() const { return Tail; }
	void PrintLink() const;
};