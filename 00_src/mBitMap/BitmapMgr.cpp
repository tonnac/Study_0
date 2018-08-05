#include "BitmapMgr.h"

void BitmapMgr::AddCache(int ikey, T_STR szName, Bitmap * pData)
{
	KCacheData KCache;
	KCache.m_iKey = ikey;
	KCache.m_strName = szName;
	KCache.m_pBitmap = pData;
	if (m_mapKCacheList.size() >= 3)
	{
		m_mapKCacheList.pop_front();
	}
	m_mapKCacheList.push_back(KCache);
}
int BitmapMgr::getCache(T_STR szName)
{
	std::list<KCacheData>::iterator iter;
	for (iter = m_mapKCacheList.begin(); iter != m_mapKCacheList.end(); iter++)
	{
		KCacheData & KCache = *iter;
		if (KCache.m_strName == szName)
		{
			return KCache.m_iKey;
		}
	}
	return -1;
}
Bitmap * BitmapMgr::getCache(int iKey)
{
	std::list<KCacheData>::iterator iter;
	for (iter = m_mapKCacheList.begin(); iter != m_mapKCacheList.end(); iter++)
	{
		KCacheData & KCache = *iter;
		if (KCache.m_iKey == iKey)
		{
			return KCache.m_pBitmap;
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
	if (pBitmap->LoadFile(szLoadFile))
	{
		AddCache(m_iIndex + 1, szLoadFile, pBitmap);
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
