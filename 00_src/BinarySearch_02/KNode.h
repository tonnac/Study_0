#pragma once
#include "CmpClass.h"

struct KNode
{
	KNode(CmpClass * addclass = 0);
	~KNode();
	CmpClass * m_kCclass;
	KNode * m_pParent;
	KNode * m_pLeft;
	KNode * m_pRight;
};

