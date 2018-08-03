#pragma once
#include "KNode.h"
class BinSearchTree
{
public:
	bool AddTree(CmpClass * src);
	void DeleteTree(CmpClass * src);
	void DeleteTree(const int & iValue);
	void DeleteAll();
	KNode * SearchTree(KNode * root, const CmpClass * src);
	KNode * SearchTree(KNode * root, const int & iValue);
	void PrintTree();
	BinSearchTree();
	~BinSearchTree();
private:
	KNode * rootNode;
	void Print(KNode * Node);
	void HangNode(KNode * Node, KNode * AddNode);
	void DeHang(KNode * DelNode);
	KNode * MaxNode(KNode * Node);
	void DeleteList(KNode *& root);
};

