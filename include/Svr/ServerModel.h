#pragma once
#include "Thread.h"

struct User;

class ServerModel : public Thread
{
public:
	ServerModel();
	virtual ~ServerModel();
public:
	virtual void Initialize() = 0;
	virtual void Release() = 0;
	virtual bool Run() = 0;
	virtual void AddUser(const User* user);
};