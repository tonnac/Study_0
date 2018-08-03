#pragma once

#define MAX(a,b) ( (a) > (b) ? (a) : (b) )
using NData = int;

struct Node
{
	NData m_nData;
	int m_iDepth;
	Node * m_pLeft;
	Node * m_pRight;
	Node(NData data = 0) : m_nData(data), m_pLeft(nullptr), m_pRight(nullptr), m_iDepth(1) {}
};

Node * insert(Node * pRoot, NData iData);
Node * ReBalance(Node * nNode);
Node * updateHeight(Node * pNode);
int getHeight(Node * pNode);
Node * LRotate(Node * pNode);
Node * RRotate(Node * pNode);