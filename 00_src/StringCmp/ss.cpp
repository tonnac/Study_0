#include <string>
#include <iostream>
#include <cstring>
#include <Windows.h>

using namespace std;

int main()
{
	string a = "qq\n";
	char buf1[256] = { 0, };
	char buf2[256] = { 0, };

	CopyMemory(buf1, a.data(), a.length());
	CopyMemory(buf2, a.data(), a.length() - 1);

	cout << buf1 << endl;
	cout << buf2 << endl;

	return 0;
}