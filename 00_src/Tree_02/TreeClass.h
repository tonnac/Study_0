#pragma once


template <class K>
class TreeClass
{
public:
	void AddTree(const K& data);
	bool AddTree(TreeClass * Node);
	void BuildTree(TreeClass * Node);
	void PRINT(const TreeClass * Node) const;
	void Delete(TreeClass * Node);
	TreeClass();
	~TreeClass();
private:
	static int m_iCount;
	int m_iDepth;
	K m_Kvalue;
	TreeClass * m_pLeft;
	TreeClass * m_pRight;
};

