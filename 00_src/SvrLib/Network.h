#pragma once
#include "SvrObject.h"
class Network : public SvrObject 
{
public:
	SOCKET m_Sock;
public:
	bool Set(const u_short port, const char* address = 0);
	void Release();
public:
	Network();
	virtual ~Network();
};