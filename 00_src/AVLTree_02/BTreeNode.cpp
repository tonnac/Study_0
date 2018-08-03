#include "BTreeNode.h"
#include <iostream>

BTreeNode::BTreeNode(BData data) : m_bData(data), m_pLeft(nullptr), m_pRight(nullptr)
{
	ptr = &BTreeNode::ShowData;
}
void BTreeNode::Setfp(FP a)
{
	ptr = a;
}
BData BTreeNode::getData() const
{
	return m_bData;
}
void BTreeNode::setLeft(BTreeNode * newtree)
{
	m_pLeft = newtree;
}
void BTreeNode::setRight(BTreeNode * newtree)
{
	m_pRight = newtree;
}
void BTreeNode::SetData(const BData& data)
{
	m_bData = data;
}
void BTreeNode::PreorderTraverse()
{
	if (this != nullptr)
	{
		m_pLeft->PreorderTraverse();
		m_pRight->PreorderTraverse();
		(this->*ptr)(m_bData);
	}
}
void BTreeNode::InorderTraverse()
{
	if (this != nullptr)
	{
		m_pLeft->InorderTraverse();
		m_pRight->InorderTraverse();
		(this->*ptr)(m_bData);
	}
}
void BTreeNode::PostorderTraverse()
{
	if (this != nullptr)
	{
		m_pLeft->PostorderTraverse();
		m_pRight->PostorderTraverse();
		(this->*ptr)(m_bData);
	}
}
bool BTreeNode::operator < (const BTreeNode& cmpNode)
{
	if (m_bData < cmpNode.getData())
		return true;
	return false;
}
bool BTreeNode::operator > (const BTreeNode& cmpNode)
{
	if (m_bData > cmpNode.getData())
		return true;
	return false;
}
bool BTreeNode::operator == (const BTreeNode& cmpNode)
{
	if (m_bData == cmpNode.getData())
		return true;
	return false;
}
bool BTreeNode::operator < (const BData& cmpData)
{
	if (m_bData < cmpData)
		return true;
	return false;
}
bool BTreeNode::operator > (const BData& cmpData)
{
	if (m_bData > cmpData)
		return true;
	return false;
}
bool BTreeNode::operator == (const BData& cmpData)
{
	if (m_bData == cmpData)
		return true;
	return false;
}
BTreeNode * BTreeNode::getLeft() const
{
	return m_pLeft;
}
BTreeNode * BTreeNode::getRight() const
{
	return m_pRight;
}

BTreeNode * BTreeNode::InsertNode(BTreeNode ** rootNode, BTreeNode * newtree)
{
	if (**rootNode > *newtree)
	{
		if((*rootNode)->m_pLeft)
			InsertNode(&((*rootNode)->m_pLeft), newtree);
		else
			(*rootNode)->m_pLeft = newtree;
	}
	else if (**rootNode < *newtree)
	{
		if ((*rootNode)->m_pRight)
			InsertNode(&((*rootNode)->m_pRight), newtree);
		else
			(*rootNode)->m_pRight = newtree;
	}
	*rootNode = Rebalance(rootNode);
	return *rootNode;
}
BTreeNode * BTreeNode::SearchNode(BTreeNode * rootNode, const BData& data)
{
	if (*rootNode < data)
	{
		if (rootNode->m_pRight)
			return SearchNode(rootNode->m_pRight,data);
		return rootNode;
	}
	else if (*rootNode > data)
	{
		if (rootNode->m_pLeft)
			return SearchNode(rootNode->m_pLeft,data);
		return rootNode;
	}
	else
		return rootNode;
}
BTreeNode * BTreeNode::SearchNode(BTreeNode * rootNode, BTreeNode * newtree)
{
	if (*rootNode < *newtree)
	{
		if (rootNode->m_pRight)
			return SearchNode(rootNode->m_pRight,newtree);
		return rootNode;
	}
	else if (*this > *newtree)
	{
		if (rootNode->m_pLeft)
			return SearchNode(rootNode->m_pLeft, newtree);
		return rootNode;
	}
	else
		return rootNode;
}
BTreeNode * BTreeNode::DeleteNode(BTreeNode ** rootNode,const BData& delData)
{
	BTreeNode * delNode = SearchNode(*rootNode,delData);
	if (!(*delNode == delData))
	{
		std::cout << "찾는값이 존재하지않음" << std::endl;
		return nullptr;
	}
	if (delNode->m_pLeft && delNode->m_pRight)
	{
		BTreeNode * tempR = delNode->getRight();
		while (tempR->getLeft() != nullptr)
		{
			tempR = tempR->getLeft();
		}
		BData swap = delNode->getData();
		delNode->SetData(tempR->getData());
		tempR->SetData(swap);
		delNode = tempR;
	}

	BTreeNode * parent = getParent(delNode);
	BTreeNode * child = (delNode->getRight() ? delNode->getRight() : delNode->getLeft());
	if (parent)
	{
		if (delNode == parent->getRight())
		{
			parent->setRight(child);
		}
		else
		{
			parent->setLeft(child);
		}
	}
	else
	{
		*rootNode = child;
	}
	delete delNode;
	return Rebalance(rootNode);
}

int BTreeNode::Heightdiff(BTreeNode * Node)
{
	BTreeNode * LeftNode = Node->getLeft();
	BTreeNode * RightNode = Node->getRight();

	int LeftH = getHeight(LeftNode);
	int RightH = getHeight(RightNode);


	return LeftH - RightH;
}
BTreeNode * BTreeNode::Rebalance(BTreeNode ** rootNode)
{
	int hDiff = Heightdiff(*rootNode);
	if (hDiff >= 2)
	{
		if (getHeight((*rootNode)->m_pLeft) > 0)
			*rootNode = RotationLL(*rootNode);
		else
			*rootNode = RotationLR(*rootNode);
	}
	if (hDiff <= -2)
	{
		if (getHeight((*rootNode)->m_pRight) > 0)
			*rootNode = RotationRR(*rootNode);
		else
			*rootNode = RotationRL(*rootNode);
	}

	return *rootNode;
}
BTreeNode * BTreeNode::RotationLL(BTreeNode * rNode)
{
	BTreeNode * cNode = rNode->getLeft();

	rNode->m_pLeft = cNode->m_pRight;
	cNode->m_pRight = rNode;

	return cNode;
}
BTreeNode * BTreeNode::RotationRR(BTreeNode * rNode)
{
	BTreeNode * cNode = rNode->m_pRight;

	rNode->m_pRight = cNode->m_pLeft;
	cNode->m_pLeft = rNode;

	return cNode;
}
BTreeNode * BTreeNode::RotationLR(BTreeNode * rNode)
{
	BTreeNode * cNode = rNode->m_pLeft;
	cNode = RotationRR(cNode);
	return RotationLL(rNode);
}
BTreeNode * BTreeNode::RotationRL(BTreeNode * rNode)
{
	BTreeNode * cNode = rNode->m_pRight;
	cNode = RotationLL(cNode);
	return RotationRR(rNode);
}

int BTreeNode::getHeight(BTreeNode * Node)
{
	if (Node == nullptr)
		return 0;

	int Lefth;
	int Righth;

	Lefth = getHeight(Node->m_pLeft);
	Righth = getHeight(Node->m_pRight);

	if (Lefth > Righth)
		return Lefth + 1;
	else
		return Righth + 1;
}
BTreeNode * BTreeNode::getParent(BTreeNode * src)
{
	BTreeNode * ptr = nullptr;
	BTreeNode * LeftNode = this->getLeft();
	BTreeNode * RightNode = this->getRight();
	if (LeftNode == src || RightNode == src)
		return this;
	if (LeftNode != src && RightNode != src)
	{
		if (LeftNode)
			ptr = LeftNode->getParent(src);
		if (RightNode)
			ptr = RightNode->getParent(src);
	}
	return ptr;
}
void BTreeNode::ShowData(BData data)
{
	std::cout << data << std::endl;
}