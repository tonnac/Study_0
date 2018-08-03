#include "BinSearchTree.h"

bool BinSearchTree::AddTree(CmpClass * src)
{
	KNode * temp = SearchTree(rootNode, src);
	if (temp)
	{
		if (*(temp->m_kCclass) == *src)
			return false;
	}
	KNode * NewNode = new KNode(src);
	HangNode(temp, NewNode);
	return true;
}
void BinSearchTree::DeleteTree(CmpClass * src)
{
	KNode * temp = SearchTree(rootNode, src);
	if (*(temp->m_kCclass) == *src)
	{
		DeHang(temp);
	}
	return;
}
void BinSearchTree::DeleteTree(const int & iValue)
{
	KNode * temp = SearchTree(rootNode, iValue);
	if (temp->m_kCclass->getValue() == iValue)
	{
		DeHang(temp);
	}
	return;
}
void BinSearchTree::DeleteAll()
{
	DeleteList(rootNode);
}
KNode * BinSearchTree::SearchTree(KNode * root, const CmpClass * src)
{
	if (root == nullptr)
	{
		return nullptr;
	}

	if (*(root->m_kCclass) > *src)
	{
		if(root->m_pLeft)
			return SearchTree(root->m_pLeft, src);
		return root;
	}
	else if (*(root->m_kCclass) < *src)
	{
		if(root->m_pRight)
			return SearchTree(root->m_pRight, src);
		return root;
	}
	else
	{
		return root;
	}
}
KNode * BinSearchTree::SearchTree(KNode * root, const int & iValue)
{
	if (root == nullptr)
	{
		return nullptr;
	}

	if (root->m_kCclass->getValue() > iValue)
	{
		if (root->m_pLeft)
			return SearchTree(root->m_pLeft, iValue);
		return root;
	}
	else if (root->m_kCclass->getValue() < iValue)
	{
		if (root->m_pRight)
			return SearchTree(root->m_pRight, iValue);
		return root;
	}
	else
	{
		return root;
	}
}

void BinSearchTree::PrintTree()
{
	Print(rootNode);
}

BinSearchTree::BinSearchTree() : rootNode(nullptr)
{}


BinSearchTree::~BinSearchTree()
{
	DeleteAll();
}

void BinSearchTree::Print(KNode * Node)
{
	if (Node != nullptr)
	{
		Print(Node->m_pLeft);
		std::cout << *(Node->m_kCclass);
		Print(Node->m_pRight);
	}
}
void BinSearchTree::HangNode(KNode * Node, KNode * AddNode)
{
	if (Node == nullptr)
	{
		rootNode = AddNode;
		return;
	}
	if (*(Node->m_kCclass) > *(AddNode->m_kCclass))
	{
		Node->m_pLeft = AddNode;
		AddNode->m_pParent = Node;
	}
	else if (*(Node->m_kCclass) < *(AddNode->m_kCclass))
	{
		Node->m_pRight = AddNode;
		AddNode->m_pParent = Node;
	}
}

void BinSearchTree::DeHang(KNode * DelNode)
{
	if (DelNode->m_pLeft && DelNode->m_pRight)
	{
		KNode * temp = MaxNode(DelNode->m_pLeft);

		CmpClass * pl = temp->m_kCclass;
		temp->m_kCclass = DelNode->m_kCclass;
		DelNode->m_kCclass = pl;

		DelNode = temp;
	}

	KNode * pa = DelNode->m_pParent;
	KNode * child = (DelNode->m_pLeft) ? DelNode->m_pLeft : DelNode->m_pRight;
	if (pa)
	{
		if (pa->m_pLeft == DelNode)
		{
			pa->m_pLeft = child;
		}
		else if (pa->m_pRight == DelNode)
		{
			pa->m_pRight = child;
		}
	}
	else
	{
		child = rootNode;
	}
	if (child)
	{
		child->m_pParent = pa;
	}
	delete DelNode;
}


KNode * BinSearchTree::MaxNode(KNode * Node)
{
	if (Node == nullptr)
	{
		return nullptr;
	}
	if (Node->m_pRight)
		return MaxNode(Node->m_pRight);
	return Node;
}

void BinSearchTree::DeleteList(KNode *& root)
{
	if (root != nullptr)
	{
		DeleteList(root->m_pLeft);
		DeleteList(root->m_pRight);
		delete root;
		root = nullptr;
	}
}