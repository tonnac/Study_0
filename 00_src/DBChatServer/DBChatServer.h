#pragma once
#include "Server.h"

enum class MENU : unsigned char
{
	SERVERQUIT = 0,
	USERINFO,
	USERBAN,
	DATABASE,
};

class ChatServer : public Server
{
public:
	void							Run() override;
private:
	u_short							PortSet() override;

	void							ShowUser();
	void							UserBan();
	void							DataBase();

	void							AddDB();
	void							EditDB();
	bool							EditUser(const std::string ID);
	void							DeleteDB();

	User*							SearchByID(char * IPAddr);
	User*							SearchByPort(char * IPAddr);
	User*							SearchByIP(char * IPAddr);
};