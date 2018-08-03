#pragma once
#include <string>
#include <tchar.h>
#include <ostream>

using C_STR = std::basic_string<char>;
using W_STR = std::basic_string<wchar_t>;
using T_STR = std::basic_string<TCHAR>;

class KJpg
{
private:
	friend std::wostream& operator << (std::wostream&, KJpg*);
	T_STR m_strName;
public:
	bool Load(T_STR);
	T_STR getName();
	KJpg();
	~KJpg();
};

