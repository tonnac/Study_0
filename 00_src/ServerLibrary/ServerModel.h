#pragma once
#include "Thread.h"

struct User;

enum class IOMODEL : uint8_t
{
	IOCP = 0,
	Select,
	WsaEvent,
	WsaAsync,
	Overlapped
};

class ServerModel : public Thread
{
protected:
	ServerModel();
public:
	virtual ~ServerModel();
public:
	static std::unique_ptr<ServerModel> CreateServerModel(const IOMODEL& modeltype);
	virtual void Initialize() = 0;
	virtual void Release() = 0;
	virtual bool Run() = 0;
	virtual void AddUser(const User* user);
};