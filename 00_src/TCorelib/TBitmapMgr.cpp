#include "TBitmapMgr.h"

void  TBitmapMgr::AddChche(int ikey, 
	T_STR name, 
	TBitmap* pData)
{
	TCacheData cache;
	cache.iKey = ikey;
	cache.name = name;
	cache.m_pBitmap = pData;
	if (m_mapCacheList.size() >= 3)
	{
		m_mapCacheList.pop_front();
	}
	m_mapCacheList.push_back(cache);
}
int  TBitmapMgr::GetChche(T_STR szName)
{
	std::list<TCacheData>::iterator iter;
	for (iter = m_mapCacheList.begin();
		iter != m_mapCacheList.end();
		iter++)
	{
		TCacheData& cache= *iter;
		if (cache.name == szName)
		{
			return cache.iKey;
		}
	}
	return -1;
}
TBitmap*  TBitmapMgr::GetChche(int iKey)
{
	std::list<TCacheData>::iterator iter;
	for (iter = m_mapCacheList.begin();
		iter != m_mapCacheList.end();
		iter++)
	{
		TCacheData& cache = *iter;
		if (cache.iKey == iKey)
		{
			return cache.m_pBitmap;
		}
	}
	return NULL;
}
int	TBitmapMgr::Load(T_STR szLoadFile)
{
	T_STR szName = szLoadFile;
	int iKey = GetChche(szName);
	if (iKey > 0)
	{
		return iKey;
	}
	std::map<int, TBitmap*>::iterator iter;
	for (iter = m_mapList.begin();
		iter != m_mapList.end();
		iter++)
	{
		TBitmap* pBitmap = (TBitmap*)(*iter).second;
		if (pBitmap->m_szName == szName)
		{
			AddChche((*iter).first, szName,
				pBitmap);
			return (*iter).first;
		}
	}
	TBitmap* pBitmap = new TBitmap;
	if (pBitmap->Load(szLoadFile))
	{
		m_mapList.insert(std::make_pair(++m_iInex, pBitmap));
		AddChche(m_iInex, szName,
			pBitmap);
		return m_iInex;
	}
	return -1;
}
TBitmap* TBitmapMgr::GetPtr(int iKey)
{
	TBitmap* pBitmap = GetChche(iKey);
	if (pBitmap != NULL)
	{
		return pBitmap;
	}
	std::map<int, TBitmap*>::iterator iter;
	iter = m_mapList.find(iKey);
	if (iter == m_mapList.end())
		return NULL;	
	return (*iter).second;
}
bool TBitmapMgr::Release()
{
	std::map<int, TBitmap*>::iterator iter;
	for (iter = m_mapList.begin();
		iter != m_mapList.end();
		iter++)
	{
		TBitmap* pBitmap = (TBitmap*)(*iter).second;
		pBitmap->Release();
		delete pBitmap;
	}
	m_mapList.clear();
	return true;
}
TBitmapMgr::TBitmapMgr()
{
	m_iInex = 0;
}
TBitmapMgr::~TBitmapMgr()
{
	Release();
}
