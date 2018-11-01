#include <iostream>
#include <string>
#include <memory>
#include <Windows.h>
#include <sstream>

using namespace std;

void chww(char* ee)
{
	ee[0] = 'e';
	ee[1] = 'q';
}

string retchar(const wchar_t* src)
{
	string retstr;
	int iLength = WideCharToMultiByte(CP_ACP, 0, src, -1, nullptr, 0, nullptr, nullptr);
	WideCharToMultiByte(CP_ACP, 0, src, -1, const_cast<char*>(retstr.c_str()), iLength, nullptr, nullptr);
	void * ptr = (void*)retstr.data();
	return retstr;
}

int main()
{
	char buf[10] = { 0, };
	char buf1[5];
	
	cin >> noskipws >> buf;
	cout << buf;

	


	const wchar_t wide[] = L"dsssdddaa";
	void * ptr;
	{
		string rr = retchar(wide);

		ptr = (void*)rr.data();
		cout << (char*)ptr;
	}
	cout << (char*)ptr;

	return 0;
}