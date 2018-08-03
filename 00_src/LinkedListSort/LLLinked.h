#pragma once
#include "LList.h"

class LLLinked
{
public:
	using FP = LList * (LLLinked::*)(LList*, LList*);
	LList * m_pHead;
	LList * m_pTail;
	LList * AscSearchNode(LList * end, LList * NewNode);
	LList * DesSearchNode(LList * end, LList * NewNode);
	void Sortrule(FP fp);
public:
	FP ad;
	void Show() const;
	void push(const int & iValue);
	void push(LList& src);
	LLLinked();
	~LLLinked();
};

