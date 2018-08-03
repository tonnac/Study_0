#pragma once

using HData = int;

struct HNode
{
	HData data;
	HNode * m_pLeft;
	HNode * m_pRight;
};

class BSTree
{
	using BSFP = void(BSTree::*)(HNode*);
public:
	BSTree();
	~BSTree();
public:
	HNode * Search(const HData& src) const;
	bool insert(const HData& src);
	bool Delete(const HData& src);
private:
	void HangNode(HNode * pNode, const HData& src);
	HNode * getParent(HNode * pNode, const HData& src);
	HNode * Searchtree(HNode * pNode, const HData& src) const;
	bool insertTree(HNode *& pNode, const HData& src);
	bool DeleteNode(HNode *& pNode, const HData& src);
private:
	int getHeight(const HNode * pNode) const;
	int getDiff(const HNode * pNode) const;
	HNode * RotateLL(HNode * pNode);
	HNode * RotateRR(HNode * pNode);
	HNode * RotateLR(HNode * pNode);
	HNode * RotateRL(HNode * pNode);
	HNode * Rebalancing(HNode * pNode);
private:
	void PreorderTraverse(HNode * pNode);
	void InorderTraverse(HNode * pNode);
	void PostorderTraverse(HNode * pNode);
	void ShowTree(HNode * pNode) const;
	void DeleteTree(HNode * pNode);
private:
	BSFP Func;
	HNode * m_pRootNode;
};

