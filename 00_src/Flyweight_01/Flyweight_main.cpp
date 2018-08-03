#include "KJpgMgr.h"
#include <iostream>

int main()
{
	int iKey = i_JpgMgr.Load(_T("1.bmp"));
	i_JpgMgr.Load(_T("2.bmp"));
	i_JpgMgr.Load(_T("3.bmp"));
	i_JpgMgr.Load(_T("4.bmp"));
	std::wcout << i_JpgMgr.getPtr(1) << std::endl;
	std::wcout << i_JpgMgr.getPtr(3) << std::endl;
	i_JpgMgr.Load(_T("5.bmp"));



	return 0;
}