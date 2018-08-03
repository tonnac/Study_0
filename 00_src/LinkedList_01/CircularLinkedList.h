#pragma once
#include "LinkedList.h"
class CircularLinkedList : public LinkedList
{
private:

public:
	CircularLinkedList();
	void AddLink(const int& Value);
	void AddLink(Node * data);
	void DelLink(const int& Value);
	Node* DelLink(Node * data);
};

