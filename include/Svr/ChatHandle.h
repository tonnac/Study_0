#pragma once
#include "ServerObj.h"

enum class MENU : unsigned char
{
	USERINFO = 1,
	SERVERINFO,
	USERBAN,
	SERVERQUIT = 0
};

class ChatHandle
{
public:
	u_short Initialize();
	void Run();
private:
	void ShowUser();
	void ShowServer();
	void UserBan();
};