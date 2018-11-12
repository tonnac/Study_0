#include "DBChatClient.h"

int main(void)
{
	ChatClient chat;
	if (!chat.Initialize())
	{
		return -1;
	}
	chat.Run();

	return 0;
}