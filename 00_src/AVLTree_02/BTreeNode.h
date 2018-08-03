#pragma once

using BData = int;
class BTreeNode
{
public:
	using FP = void (BTreeNode::*)(BData);
	BTreeNode(BData data = 0);
	void Setfp(FP a);
	BData getData() const;
	void setLeft(BTreeNode * newtree);
	void setRight(BTreeNode * newtree);
	void SetData(const BData& data);
	void PreorderTraverse();
	void InorderTraverse();
	void PostorderTraverse();
	bool operator < (const BTreeNode& cmpNode);
	bool operator > (const BTreeNode& cmpNode);
	bool operator == (const BTreeNode& cmpNode);
	bool operator < (const BData& cmpData);
	bool operator > (const BData& cmpData);
	bool operator == (const BData& cmpData);
	BTreeNode * getLeft() const;
	BTreeNode * getRight() const;
public:
	BTreeNode * InsertNode(BTreeNode ** rootNode, BTreeNode * newtree);
	BTreeNode * SearchNode(BTreeNode * rootNode, const BData& data);
	BTreeNode * SearchNode(BTreeNode * rootNode, BTreeNode * newtree);
	BTreeNode * DeleteNode(BTreeNode ** rootNode, const BData& delData);
public:
	int Heightdiff(BTreeNode * Node);
	BTreeNode * Rebalance(BTreeNode ** rootNode);
	BTreeNode * RotationLL(BTreeNode * rNode);
	BTreeNode * RotationRR(BTreeNode * rNode);
	BTreeNode * RotationLR(BTreeNode * rNode);
	BTreeNode * RotationRL(BTreeNode * rNode);
private:
	int getHeight(BTreeNode * Node);
	BTreeNode * getParent(BTreeNode * src);
	void ShowData(BData data);
	FP ptr;
	BData m_bData;
	BTreeNode * m_pLeft;
	BTreeNode * m_pRight;
};