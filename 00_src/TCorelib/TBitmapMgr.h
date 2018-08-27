#pragma once
#include "TBitmap.h"
struct TCacheData
{
	int		iKey;
	T_STR	name;
	TBitmap* m_pBitmap;
};
class TBitmapMgr : public TSingleton<TBitmapMgr>
{
	friend class TSingleton<TBitmapMgr>;
	std::map<int, TBitmap*> m_mapList;
	std::list<TCacheData> m_mapCacheList;
	int		m_iInex;
public:
	int	Load(T_STR szLoadFile);
	int  GetChche(T_STR szName);
	bool Release();
	TBitmap*  GetPtr(int iKey);
	TBitmap*  GetChche(int iKey);
	void  AddChche(int ikey,
		T_STR name,
		TBitmap* pData);
	
protected:
	TBitmapMgr();
public:
	virtual ~TBitmapMgr();
};
#define I_BitmapMgr TBitmapMgr::GetInstance()

