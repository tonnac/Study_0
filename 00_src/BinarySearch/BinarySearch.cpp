#include <iostream>


#define SAFE_NEW(p,N)	{if(!p) p = new N;}
#define SAFE_NEW_ARRAY(p,N,s)	{if(!p) p = new N[s]; if(p) memeset(p,0,sizeof(N)*s);}
#define SAFE_DEL_ARRAY(p)	{if(!p) delete[] p; p=nullptr;}
#define SAFE_NEW_VALUE(p,N,v)	{if(!p) p = new N(v);}
#define SAFE_DELETE(p)	if(p) {delete p; (p) = nullptr;}
#define SAFE_ZERO(p) {p = nullptr;}



struct Node
{
	int m_iValue;
	int m_iDepth;
	Node * m_pLeft;
	Node * m_pRight;
	Node(int idata) : m_iValue(idata), m_pLeft(nullptr), m_pRight(nullptr), m_iDepth(0) {}
	//	void Add(Node*);
};
void BinaryNode(Node * pParentNode, int iData)
{
	if (pParentNode == nullptr) return;
	if (pParentNode->m_iValue > iData)
	{
		if (pParentNode->m_pLeft == nullptr)
			pParentNode->m_pLeft = new Node(iData);
		else
			BinaryNode(pParentNode->m_pLeft, iData);
	}
	else
	{
		if (pParentNode->m_pRight == nullptr)
			pParentNode->m_pRight = new Node(iData);
		else
			BinaryNode(pParentNode->m_pRight, iData);
	}
}
void PRINT(Node * pParentNode)
{
	//std::cout << pParentNode->m_iValue << std::endl;		// ÀüÀ§Å½»ö
	if (pParentNode != nullptr)
	{
		PRINT(pParentNode->m_pLeft);
		//std::cout << pParentNode->m_iValue << std::endl;  // ÁßÀ§Å½»ö
		PRINT(pParentNode->m_pRight);
		std::cout << pParentNode->m_iValue << std::endl;	// ÈÄÀ§Å½»ö
	}
}
void Delete(Node *& pParentNode)
{
	if (pParentNode != nullptr)
	{
		Delete(pParentNode->m_pLeft);
		Delete(pParentNode->m_pRight);
		SAFE_DELETE(pParentNode);
	}
}

Node * g_pRoot = nullptr;
int g_iIndex = 0;
int g_iData[10] = { 5,0,4,7,8,3,9,2,6,1 };

int main(void)
{
	SAFE_NEW_VALUE(g_pRoot, Node, g_iData[g_iIndex++]);

	for (int i = 1; i < 10; i++)
	{
		BinaryNode(g_pRoot, g_iData[i]);
	}

	PRINT(g_pRoot);
	Delete(g_pRoot);

	return 0;
}