#pragma once
#include <string>
#include <tchar.h>

using C_STR = std::basic_string<char>;
using W_STR = std::basic_string<wchar_t>;
using T_STR = std::basic_string<TCHAR>;

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

class Bitmap
{
	T_STR m_szName;
public:
	bool Load(T_STR szLoadFile)
	{
		m_szName = szLoadFile;
		return true;
	}
	T_STR getName()
	{
		return m_szName;
	}
	Bitmap();
	virtual ~Bitmap();
};

