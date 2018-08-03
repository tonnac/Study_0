#include "KJpgMgr.h"


bool CacheData::operator == (const int& iValue)
{
	if (m_iKey == iValue)
		return true;
	return false;
}
bool CacheData::operator == (const T_STR& strName)
{
	if (m_strName == strName)
		return true;
	return false;
}



void KJpgMgr::addCache(T_STR strname, int iValue, KJpg* pJpg)
{
	CacheData temp;
	temp.m_iKey = iValue;
	temp.m_strName = strname;
	temp.p_pKJpg = pJpg;
	if (m_cacheData.size() >= 3)
		m_cacheData.pop_front();
	m_cacheData.push_back(temp);
}
int KJpgMgr::getCache(T_STR strName)
{
	listiterator lit = m_cacheData.begin();
	for (; lit != m_cacheData.end(); lit++)
	{
		if (*lit == strName)
			return lit->m_iKey;
	}
	return -1;
}
KJpg* KJpgMgr::getCache(int iKey)
{
	listiterator lit = m_cacheData.begin();
	for (; lit != m_cacheData.end(); lit++)
	{
		if (*lit == iKey)
			return lit->p_pKJpg;
	}
	return nullptr;
}

KJpg * KJpgMgr::getPtr(int iKey)
{
	KJpg * rn = getCache(iKey);
	if (rn)
	{
		return rn;
	}
	mapiterator it;
	it = m_maplist.find(iKey);
	if (it == m_maplist.end())
		return nullptr;
	return it->second;
}
int KJpgMgr::Load(T_STR szLoadfile)
{
	int iKey = getCache(szLoadfile);
	if (iKey > 0)
	{
		return iKey;
	}

	mapiterator it;
	for (it = m_maplist.begin(); it != m_maplist.end(); it++)
	{
		KJpg * pJpg = static_cast<KJpg*>(it->second);
		if (pJpg->getName() == szLoadfile)
		{
			addCache(szLoadfile, it->first, it->second);
			return it->first;
		}
	}
	KJpg * pJpg = new KJpg;
	if (pJpg->Load(szLoadfile))
	{
		addCache(szLoadfile,m_iIndex+1,pJpg);
		m_maplist.insert(std::make_pair(++m_iIndex, pJpg));
		return m_iIndex;
	}
	return -1;
}

KJpgMgr::KJpgMgr() : m_iIndex(0)
{
}


KJpgMgr::~KJpgMgr()
{
}
