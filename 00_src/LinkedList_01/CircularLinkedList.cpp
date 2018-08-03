#include "CircularLinkedList.h"



CircularLinkedList::CircularLinkedList() : LinkedList()
{}

void CircularLinkedList::AddLink(const int& Value)
{
	LinkedList::AddLink(Value);
	Node* temp = LinkedList::GetTail();
	temp->m_pNext = LinkedList::Head;
}
void CircularLinkedList::AddLink(Node * data)
{
	LinkedList::AddLink(data);
	Node* temp = LinkedList::GetTail();
	temp->m_pNext = LinkedList::Head;
}
void CircularLinkedList::DelLink(const int& Value)
{
	LinkedList::DelLink(Value);
}
Node* CircularLinkedList::DelLink(Node * data)
{
	Node * rn = data->m_pNext;
	LinkedList::DelLink(data);
	return rn;
}