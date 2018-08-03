#pragma once
#include "KJpg.h"
#include <map>
#include <list>
template <class K>
class Singleton
{
protected:
	Singleton() {}
public:
	static K& getInst()
	{
		static K inst;
		return inst;
	}
};

struct CacheData
{
	int m_iKey;
	T_STR m_strName;
	KJpg * p_pKJpg;

	bool operator == (const int& iValue);
	bool operator == (const T_STR& strName);
};




class KJpgMgr : public Singleton<KJpgMgr>
{
	using mapiterator = std::map<int, KJpg*>::iterator;
	using listiterator = std::list<CacheData>::iterator;
	friend class Singleton<KJpgMgr>;
	int m_iIndex;
	std::map<int, KJpg*> m_maplist;
	std::list<CacheData> m_cacheData;
private:
	void addCache(T_STR, int, KJpg*);
	int getCache(T_STR);
	KJpg* getCache(int);
public:
	KJpg * getPtr(int);
	int Load(T_STR);

	KJpgMgr();
	~KJpgMgr();

};


#define i_JpgMgr KJpgMgr::getInst()