#include "BitmapMgr.h"

void BitmapMgr::AddCache(int ikey, T_STR szName, Bitmap * pData)
{
	CacheData cache;
	cache.m_iKey = ikey;
	cache.m_strName = szName;
	cache.m_pBitmap = pData;
	if (m_mapCacheList.size() >= 3)
	{
		m_mapCacheList.pop_front();
	}
	m_mapCacheList.push_back(cache);
}
int BitmapMgr::getCache(T_STR szName)
{
	std::list<CacheData>::iterator iter;
	for (iter = m_mapCacheList.begin(); iter != m_mapCacheList.end(); iter++)
	{
		CacheData & cache = *iter;
		if (cache.m_strName == szName)
		{
			return cache.m_iKey;
		}
	}
	return -1;
}
Bitmap * BitmapMgr::getCache(int iKey)
{
	std::list<CacheData>::iterator iter;
	for (iter = m_mapCacheList.begin(); iter != m_mapCacheList.end(); iter++)
	{
		CacheData & cache = *iter;
		if (cache.m_iKey == iKey)
		{
			return cache.m_pBitmap;
		}
	}
	return nullptr;
}

int BitmapMgr::Load(T_STR szLoadFile)
{
	T_STR szName = szLoadFile;
	int iKey = getCache(szLoadFile);
	if (iKey > 0)
	{
		return iKey;
	}
	std::map<int, Bitmap*>::iterator iter;
	for (iter = m_map.begin(); iter != m_map.end(); iter++)
	{
		Bitmap * pBitmap = static_cast<Bitmap*>((*iter).second);
		if (pBitmap->getName() == szName)
		{
			AddCache(iter->first, szLoadFile, iter->second);
			return (*iter).first;
		}
	}
	Bitmap * pBitmap = new Bitmap;
	if (pBitmap->Load(szLoadFile))
	{
		AddCache(m_iIndex+1, szLoadFile, pBitmap);
		m_map.insert(std::make_pair(++m_iIndex, pBitmap));
		return m_iIndex;
	}
	return -1;
}
Bitmap * BitmapMgr::getPtr(int iKey)
{
	Bitmap * pData = getCache(iKey);
	if (pData)
	{
		return pData;
	}

	std::map<int, Bitmap*>::iterator iter;
	iter = m_map.find(iKey);
	if (iter == m_map.end())
	{
		return nullptr;
	}
	return static_cast<Bitmap*>(iter->second);
}

BitmapMgr::BitmapMgr() : m_iIndex(0)
{
}
BitmapMgr::~BitmapMgr()
{
}