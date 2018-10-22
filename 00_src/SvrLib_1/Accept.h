#pragma once
#include "Thread.h"
#include "Network.h"

class Accept : public Thread
{
	Network m_network;
public:
	bool Set(const u_short port, const char* address);
	void Run() override;
public:
	Accept();
	virtual ~Accept();
};