#include "TreeClass.h"
#include <iostream>


template <class K>
int TreeClass<K>::m_iCount = 0;

template <class K>
void TreeClass<K>::AddTree(const K& data)
{
	if (this->m_pLeft == nullptr)
	{
		this->m_pLeft = new TreeClass;
		this->m_pLeft->m_iDepth = this->m_iDepth + 1;
		this->m_pLeft->m_Kvalue = data;
		return;
	}
	else if (this->m_pRight == nullptr)
	{
		this->m_pRight = new TreeClass;
		this->m_pRight->m_iDepth = this->m_iDepth + 1;
		this->m_pRight->m_Kvalue = data;
		return;
//		this->m_pRight->AddTree(data);
	}
	this->m_pLeft->AddTree(data);
}
template <class K>
bool TreeClass<K>::AddTree(TreeClass * Node)
{
	if (Node->m_iDepth > 2) return false;
	Node->m_pLeft = new TreeClass;
	Node->m_pLeft->m_iDepth = Node->m_iDepth + 1;
	Node->m_pLeft->m_Kvalue = ++m_iCount;

	Node->m_pRight = new TreeClass;
	Node->m_pRight->m_iDepth = Node->m_iDepth + 1;
	Node->m_pRight->m_Kvalue = ++m_iCount;
	return true;
}
template <class K>
void TreeClass<K>::BuildTree(TreeClass * Node)
{
	if (AddTree(Node))
	{
		BuildTree(Node->m_pLeft);
		BuildTree(Node->m_pRight);
	}
}
template <class K>
void TreeClass<K>::PRINT(const TreeClass * Node) const
{
	if (Node != nullptr)
	{
		PRINT(Node->m_pLeft);
		PRINT(Node->m_pRight);
		std::cout << Node->m_Kvalue << std::endl;
	}
}
template <class K>
void TreeClass<K>::Delete(TreeClass * Node)
{
	if (Node != nullptr)
	{
		Delete(Node->m_pLeft);
		Delete(Node->m_pRight);
		std::cout << Node->m_Kvalue << std::endl;
		delete Node;
		Node = nullptr;
	}
}
template <class K>
TreeClass<K>::TreeClass() : m_Kvalue(0), m_pLeft(nullptr), m_pRight(nullptr), m_iDepth(0)
{}

template <class K>
TreeClass<K>::~TreeClass()
{}
