#include "BSTree.h"
#include <iostream>



BSTree::BSTree() : m_pRootNode(nullptr)
{
	Func = &BSTree::DeleteTree;
}
BSTree::~BSTree()
{
	PostorderTraverse(m_pRootNode);
}

HNode * BSTree::Search(const HData& src) const
{
	return Searchtree(m_pRootNode, src);
}
bool BSTree::insert(const HData& src)
{
	return insertTree(m_pRootNode, src);
}
bool BSTree::Delete(const HData& src)
{
	return DeleteNode(m_pRootNode, src);
}

void BSTree::HangNode(HNode * pNode, const HData& src)
{
	if (pNode->data > src)
	{
		HNode * newNode = new HNode;
		newNode->data = src;
		newNode->m_pLeft = nullptr;
		newNode->m_pRight = nullptr;
		pNode->m_pLeft = newNode;
	}
	else
	{
		HNode * newNode = new HNode;
		newNode->data = src;
		newNode->m_pLeft = nullptr;
		newNode->m_pRight = nullptr;
		pNode->m_pRight = newNode;
	}
}
HNode * BSTree::getParent(HNode * pNode, const HData& src)
{
	if (pNode->data == src || (pNode->m_pLeft) == nullptr && (pNode->m_pRight) == nullptr)
		return nullptr;
	if (src < pNode->data)
	{
		if (pNode->m_pLeft->data == src)
			return pNode;
		return getParent(pNode->m_pLeft, src);
	}
	else
	{
		if ((pNode->m_pRight->data) == src)
			return pNode;
		return getParent(pNode->m_pRight, src);
	}
}
HNode * BSTree::Searchtree(HNode * pNode, const HData& src) const
{
	if (pNode->data > src)
	{
		if (pNode->m_pLeft)
			return Searchtree(pNode->m_pLeft, src);
		return nullptr;
	}
	else if (pNode->data < src)
	{
		if (pNode->m_pRight)
			return Searchtree(pNode->m_pRight, src);
		return nullptr;
	}
	else
		return pNode;
}
bool BSTree::insertTree(HNode *& pNode, const HData& src)
{
	if (pNode == nullptr)
	{
		m_pRootNode = new HNode;
		m_pRootNode->data = src;
		m_pRootNode->m_pLeft = nullptr;
		m_pRootNode->m_pRight = nullptr;
		return true;
	}

	if (pNode->data > src)
	{
		if (pNode->m_pLeft)
		{
			insertTree(pNode->m_pLeft, src);
		}
		else
		{
			HangNode(pNode, src);
		}
	}
	else if (pNode->data < src)
	{
		if (pNode->m_pRight)
		{
			insertTree(pNode->m_pRight, src);
		}
		else
		{
			HangNode(pNode, src);
		}
	}
	else
	{
		std::cout << "같은 값 입력 불가" << std::endl;
		throw false;
	}
	pNode = Rebalancing(pNode);
	return true;
}
bool BSTree::DeleteNode(HNode *& pNode, const HData& src)
{
	HNode * delNode = pNode;
	HNode * Parent = getParent(m_pRootNode, delNode->data);
	if (pNode == nullptr)
	{
		std::cout << "데이터가 존재하지않습니다." << std::endl;
		return false;
	}
	if (pNode->data > src)
		DeleteNode(pNode->m_pLeft, src);
	else if (pNode->data < src)
		DeleteNode(pNode->m_pRight, src);
	else
	{
		if (delNode->m_pLeft && delNode->m_pRight)
		{
			HNode * LeftMaxNode = pNode->m_pLeft;
			while (LeftMaxNode->m_pRight != nullptr)
			{
				LeftMaxNode = LeftMaxNode->m_pRight;
			}
			HData temp = LeftMaxNode->data;
			LeftMaxNode->data = delNode->data;
			delNode->data = temp;

			delNode = LeftMaxNode;
		}

		
		HNode * Child = (delNode->m_pLeft) ? (delNode->m_pLeft) : (delNode->m_pRight);
		if (Parent)
		{
			if (delNode == Parent->m_pLeft)
				Parent->m_pLeft = Child;
			else
				Parent->m_pRight = Child;
		}
		else
		{
			pNode = Child;
		}
		delete delNode;
	}
	if(pNode)
		pNode = Rebalancing(pNode);
	return true;
}

int BSTree::getHeight(const HNode * pNode) const
{
	int LeftH;
	int RightH;

	if (pNode == nullptr)
		return 0;

	LeftH = getHeight(pNode->m_pLeft);
	RightH = getHeight(pNode->m_pRight);

	if (LeftH > RightH)
		return LeftH + 1;
	else
		return RightH + 1;
}
int BSTree::getDiff(const HNode * pNode) const
{
	int lsh = getHeight(pNode->m_pLeft);
	int rsh = getHeight(pNode->m_pRight);

	return lsh - rsh;
}
HNode * BSTree::RotateLL(HNode * pNode)
{
	HNode * cNode = pNode->m_pLeft;

	pNode->m_pLeft = cNode->m_pRight;
	cNode->m_pRight = pNode;

	return cNode;
}
HNode * BSTree::RotateRR(HNode * pNode)
{
	HNode * cNode = pNode->m_pRight;

	pNode->m_pRight = cNode->m_pLeft;
	cNode->m_pLeft = pNode;

	return cNode;
}
HNode * BSTree::RotateLR(HNode * pNode)
{
	HNode *& cNode = pNode->m_pLeft;

	pNode->m_pLeft = RotateRR(cNode);
	return RotateLL(pNode);
}
HNode * BSTree::RotateRL(HNode * pNode)
{
	HNode * cNode = pNode->m_pRight;

	pNode->m_pRight = RotateLL(cNode);
	return RotateRR(pNode);
}
HNode * BSTree::Rebalancing(HNode * pNode)
{
	int Diff = getDiff(pNode);
	if (Diff > 1)
	{
		if (getDiff(pNode->m_pLeft) > 0)
			pNode = RotateLL(pNode);
		else
			pNode = RotateLR(pNode);
	}
	else if (Diff < -1)
	{
		if (getDiff(pNode->m_pRight) < 0)
			pNode = RotateRR(pNode);
		else
			pNode = RotateRL(pNode);
	}
	return pNode;
}

void BSTree::PreorderTraverse(HNode * pNode)
{
	if (pNode == nullptr)
		return;
	(this->*Func)(pNode);
	PreorderTraverse(pNode->m_pLeft);
	PreorderTraverse(pNode->m_pRight);
}
void BSTree::InorderTraverse(HNode * pNode)
{
	if (pNode == nullptr)
		return;
	InorderTraverse(pNode->m_pLeft);
	(this->*Func)(pNode);
	InorderTraverse(pNode->m_pRight);
}
void BSTree::PostorderTraverse(HNode * pNode)
{
	if (pNode == nullptr)
		return;
	PostorderTraverse(pNode->m_pLeft);
	PostorderTraverse(pNode->m_pRight);
	(this->*Func)(pNode);
}
void BSTree::ShowTree(HNode * pNode) const
{
	std::cout << pNode->data << std::endl;
}
void BSTree::DeleteTree(HNode * pNode)
{
	delete pNode;
}