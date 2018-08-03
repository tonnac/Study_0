#pragma once
#include "Bitmap.h"
#include <map>
#include <list>
//string a; multi-byte
//wstring a; unicode-byte

struct CacheData
{
	int m_iKey;
	T_STR m_strName;
	Bitmap * m_pBitmap;
};

class BitmapMgr : public Singleton<BitmapMgr>
{
	friend class Singleton<BitmapMgr>;
	std::map<int, Bitmap*> m_map;
	std::list<CacheData> m_mapCacheList;
	int m_iIndex;
	BitmapMgr();
private:
	void AddCache(int ikey, T_STR szName, Bitmap * pData);
	Bitmap * getCache(int iKey);
	int getCache(T_STR szName);
public:
	int Load(T_STR szLoadFile);
	Bitmap * getPtr(int iKey);
public:
	virtual ~BitmapMgr();
};

#define I_BitmapMgr BitmapMgr::getInst()