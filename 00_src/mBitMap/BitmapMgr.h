#pragma once
#include "Bitmap.h"
//string a; multi-byte
//wstring a; unicode-byte

struct KCacheData
{
	int m_iKey;
	T_STR m_strName;
	Bitmap * m_pBitmap;
};

class BitmapMgr : public Singleton<BitmapMgr>
{
	friend class Singleton<BitmapMgr>;
private:
	void								AddCache(int ikey, T_STR szName, Bitmap * pData);
	Bitmap *							getCache(int iKey);
	int									getCache(T_STR szName);
public:
	int									Load(T_STR szLoadFile);
	Bitmap *							getPtr(int iKey);
public:
	virtual ~BitmapMgr();
private:
	int									m_iIndex;
	std::map<int, Bitmap*>				m_map;
	std::list<KCacheData>				m_mapKCacheList;
	BitmapMgr();
};

#define I_BitmapMgr BitmapMgr::getInst()
