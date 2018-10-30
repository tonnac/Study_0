#pragma once
#include "Server.h"

enum class MENU : unsigned char
{
	USERINFO = 1,
	USERBAN,
	SERVERQUIT = 0
};

class ChatServer : public Server
{
public:
	void							Run() override;
private:
	u_short							PortSet() override;
	void							ShowUser();
	void							UserBan();
	User*							SearchByID(char * IPAddr);
	User*							SearchByPort(char * IPAddr);
	User*							SearchByIP(char * IPAddr);
};