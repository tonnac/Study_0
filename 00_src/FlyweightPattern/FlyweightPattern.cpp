#include "BitmapMgr.h"
#include <iostream>

int main(void)
{
	Bitmap * pBitmap = nullptr;
	//I_BitmapMgr.Load(_T("../data/bitmap/qwe.bmp"));
	int iKey = I_BitmapMgr.Load(_T("kgca.bmp"));
	std::wcout << I_BitmapMgr.getPtr(iKey)->getName() << std::endl;

	iKey = I_BitmapMgr.Load(_T("kgca1.bmp"));
	std::wcout << I_BitmapMgr.getPtr(iKey)->getName() << std::endl;

	iKey = I_BitmapMgr.Load(_T("kgca2.bmp"));
	std::wcout << I_BitmapMgr.getPtr(iKey)->getName() << std::endl;

	iKey = I_BitmapMgr.Load(_T("kgca3.bmp"));
	std::wcout << I_BitmapMgr.getPtr(iKey)->getName() << std::endl;

	iKey = I_BitmapMgr.Load(_T("kgca4.bmp"));
	std::wcout << I_BitmapMgr.getPtr(iKey)->getName() << std::endl;




	iKey = I_BitmapMgr.Load(_T("kgca2.bmp"));					//캐시로 리턴
	std::wcout << I_BitmapMgr.getPtr(iKey)->getName() << std::endl;

	iKey = I_BitmapMgr.Load(_T("kgca4.bmp"));
	std::wcout << I_BitmapMgr.getPtr(iKey)->getName() << std::endl;	

	return 0;
}