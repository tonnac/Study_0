#include <memory>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <algorithm>
#include <fstream>
#include <array>
#include <codecvt>
#include <iostream>
#include <Windows.h>

using namespace std;

void InputString(ofstream& fout, const wstring& str)
{
	int size = (int)str.length();
	fout.write((char*)&size, sizeof(int));
	fout.write((char*)str.data(), sizeof(wchar_t) * size);
}

void OutputString(ifstream& fin, wstring& str)
{
	int size;
	fin.read((char*)&size, sizeof(int));
	str.resize(size);
	fin.read((char*)str.data(), sizeof(wchar_t) * size);
}

class Unicodecvt : public std::codecvt<wchar_t, char, mbstate_t>
{
protected:
	virtual bool do_always_noconv() const noexcept
	{
		return true;
	}
};

struct A
{
	A()
	{}
	A(int a) : mInt(a)
	{}
	std::string Name;
	float mFloat = -1.0f;
	int mInt = -1;
	std::vector<int> e;
};



int main()
{
	//wofstream fout(L"data.bin", ios::binary);
	//fout.imbue(locale(locale(""), new Unicodecvt));

	//wstring ee = L"asdasdasd";
	//int size = (int)ee.length();

	//fout.write((wchar_t*)&size, sizeof(int));
	//fout.write((wchar_t*)ee.data(), sizeof(wchar_t) * size);
	

	array<int, 4> dd =
	{
		1,2,3,4
	};

	array<BYTE, 4> pp =
	{

	};

	std::copy(dd.begin(), dd.end(), pp.data());

	int sz = sizeof(dd);
	//wifstream fin(L"data.bin", ios::binary);
	//fin.imbue(locale(locale(""), new Unicodecvt));
	//wstring ee;
	//int size;

	//fin.read((wchar_t*)&size, sizeof(int));
	//ee.resize(size);
	//fin.read((wchar_t*)ee.data(), sizeof(wchar_t) * size);

	return 0;
}

