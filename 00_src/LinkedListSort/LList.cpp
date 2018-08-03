#include "LList.h"


LList::LList() : m_iValue(0), m_pNext(nullptr), m_pPrev(nullptr)
{}
LList::LList(const int& number) : m_iValue(number), m_pPrev(nullptr), m_pNext(nullptr)
{}

