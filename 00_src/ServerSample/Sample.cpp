#include "Server.h"

int main()
{
	S_Server.Initialize();
	S_Server.Run();
	while (1)
	{
		if (GetAsyncKeyState(VK_F12) & 0x8000)
		{
			isExit = true;
			break;
		}
	}

	return 0;
}