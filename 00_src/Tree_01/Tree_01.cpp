#include <iostream>

int g_iMemoryCount = 0;
int g_iMemorySize = 0;

#define SAFE_NEW(p,N)	{if(!p) p = new N; g_iMemoryCount++;}

#define SAFE_NEW_ARRAY(p,N,s)	{if(!p) p = new N[s]; if(p) memeset(p,0,sizeof(N)*s);}
#define SAFE_DEL_ARRAY(p)	{if(!p) delete[] p; p=nullptr;}

#define SAFE_NEW_VALUE(p,N,v)	{if(!p) p = new N(v); g_iMemoryCount++;}
#define SAFE_DELETE(p)	if(p) {delete p; (p) = nullptr;g_iMemoryCount--;}
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
Node * g_pRoot = nullptr;
int g_iIndex = 0;
bool Add(Node * pParentNode)
{
	if (pParentNode->m_iDepth > 2) { return false; }
	Node * pLeft = nullptr;
	SAFE_NEW_VALUE(pLeft,Node,++g_iIndex);
	pLeft->m_iDepth = pParentNode->m_iDepth + 1;
	pParentNode->m_pLeft = pLeft;

	Node * pRight = nullptr;
	SAFE_NEW_VALUE(pRight, Node, ++g_iIndex);
	pRight->m_iDepth = pParentNode->m_iDepth + 1;
	pParentNode->m_pRight = pRight;
	return true;
}
void Build(Node* pParentNode)
{
	if(Add(pParentNode))
	{
		Build(pParentNode->m_pLeft);
		Build(pParentNode->m_pRight);
	}
}
void PRINT(Node * pParentNode)
{
	
	if (pParentNode != nullptr)
	{
		std::cout << pParentNode->m_iValue << std::endl;		// ÀüÀ§Å½»ö
		PRINT(pParentNode->m_pLeft);
		//std::cout << pParentNode->m_iValue << std::endl;  // ÁßÀ§Å½»ö
		PRINT(pParentNode->m_pRight);
		//std::cout << pParentNode->m_iValue << std::endl;	// ÈÄÀ§Å½»ö
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

int main(void)
{
	SAFE_NEW_VALUE(g_pRoot, Node, 0);
	Node * pNode = g_pRoot;
	Build(pNode);PRINT(pNode);
	Delete(g_pRoot);

	return 0;
}