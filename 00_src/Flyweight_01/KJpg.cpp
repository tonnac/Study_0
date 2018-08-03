#include "KJpg.h"

std::wostream& operator << (std::wostream&os, KJpg * pJpg)
{
	os << pJpg->m_strName;
	return os;
}

bool KJpg::Load(T_STR strFilename)
{
	m_strName = strFilename;
	return true;
}

T_STR KJpg::getName()
{
	return m_strName;
}

KJpg::KJpg()
{}


KJpg::~KJpg()
{
}
