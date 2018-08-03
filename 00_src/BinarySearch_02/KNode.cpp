#include "KNode.h"
#include <iostream>

KNode::KNode(CmpClass * addclass) : m_kCclass(addclass), m_pLeft(nullptr)
, m_pParent(nullptr), m_pRight(nullptr)
{}

KNode::~KNode()
{
	delete m_kCclass;
}