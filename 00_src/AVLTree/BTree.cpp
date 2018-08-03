#include "BTree.h"
#include <iostream>

Node * ReBalance(Node * nNode)
{
	return nullptr;
}

Node * insert(Node * pRoot, NData iData)
{
	if (pRoot == nullptr)
		return new Node(iData);

	if (pRoot->m_nData < iData)
	{
		pRoot->m_pRight = insert(pRoot->m_pRight, iData);
	}
	else if(pRoot->m_nData > iData)
	{
		pRoot->m_pLeft = insert(pRoot->m_pLeft, iData);
	}
	else
	{
		return pRoot;
	}

	pRoot = updateHeight(pRoot);
	
	int iBalanceFactor = getHeight(pRoot->m_pRight) - getHeight(pRoot->m_pRight);

	Node * pNewNode = new Node(iData);
	pNewNode->m_iDepth = pRoot->m_iDepth+1;

	if (pRoot->m_nData > iData)
		pRoot->m_pLeft = pNewNode;
	else
		pRoot->m_pRight = pNewNode;

	if (iBalanceFactor > 1 && 
		pRoot->m_pLeft->m_nData < iData)
	{
		return RRotate(pRoot);
	}
	else if (iBalanceFactor > 1 && 
		pRoot->m_pLeft->m_nData > iData)
	{
		pRoot->m_pLeft = LRotate(pRoot->m_pLeft);
		return RRotate(pRoot);
	}
	else if (iBalanceFactor < -1 &&
		pRoot->m_pRight->m_nData < iData)
	{
		return LRotate(pRoot);
	}
	else if (iBalanceFactor < -1 &&
		pRoot->m_pRight->m_nData > iData)
	{
		pRoot->m_pRight = RRotate(pRoot->m_pRight);
		return LRotate(pRoot);
	}

	return ReBalance(pRoot);
}
Node * updateHeight(Node * pNode)
{
	pNode->m_iDepth = 1 + MAX(getHeight(pNode->m_pLeft), getHeight(pNode->m_pRight));
}
int getHeight(Node * pNode)
{
	if (pNode == nullptr) return 0;
	return pNode->m_iDepth;
}
Node * LRotate(Node * pNode)
{
	Node * x = pNode->m_pRight;
	Node * y = x->m_pLeft;
	x->m_pLeft = pNode;
	pNode->m_pRight = y;

	x = updateHeight(x);
	pNode = updateHeight(pNode);

	return x;
}
Node * RRotate(Node * pNode)
{
	Node * x = pNode->m_pLeft;
	Node * y = x->m_pRight;
	x->m_pRight = pNode;
	pNode->m_pLeft = y;

	pNode = updateHeight(pNode);
	x = updateHeight(x);

	return x;
}