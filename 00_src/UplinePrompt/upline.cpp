#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

void upLinePrompt(int count)
{
	for (int i = 0; i < count; ++i) {
		//printf("%c[2K",27);
		cout << "\33[2K"; //line clear
		cout << "\x1b[A"; //up line (ESC [ A) must be support VT100 escape seq
	}
}

int main()
{
	while (1)
	{
		char buf[256] = { 0, };
		if (_kbhit())
		{
			cin.getline(buf, 256);
		}
		if (GetAsyncKeyState(VK_F12) & 0x8000)
		{
			cout << buf << endl;
		}
	}
	return 0;
}